#!/usr/bin/env bash
which git > /dev/null 2>&1
if [[ $? -ne 0 ]]; then
  >&2 echo 'git command not found.'
  exit 1
fi
which date > /dev/null 2>&1
if [[ $? -ne 0 ]]; then
  >&2 echo 'date command not found.'
  exit 1
fi
which gawk > /dev/null 2>&1
if [[ $? -ne 0 ]]; then
  >&2 echo 'gawk command not found.'
  exit 1
fi

function usage() {
  echo "Usage $(basename $0) [options] <directory_or_url> [<directory_or_url>...]

  OPTIONS:
    --help
      show this text and exit
    --branch
      git branch to count commits (default 'main')
    --since=<date>
      only count commits since <date> (default 'last monday')
    --until=<date>
      only count commits until <date> (default 'next sunday')
    --intervals=<file>
    --min-commits-per-interval=<n>
    --deadline=<date>
      commits after this date are not counted (default 'now')
    --deadline-commits-total=<n>
      minimum number of commits at the deadline (default 60)
    --deadline-commits-per-author=<n>
      minimum number of commits per author at the deadline (default 15)
    -i <n>|--min-insertions=<n>
      minimum number of insertions for a commit to be valid (default 0)
    -c|--count-invalid
      count invalid commits
    -w|--warn-invalid
      warn for invalid commits
    -z|--null
      separates records with the null character instead of a newline

  REMARKS:
    <date> is a string that gets passed to the \`date -d\` command (see man date)";
}

function separator {
    if [[ $nullsep -eq 1 ]]; then
      printf '%b' '\0'
    else
      printf '\n'
    fi
}

OPTIONS=i:cwn
LONGOPTS=branch:,since:,until:,intervals:,min-commits-per-interval:,deadline:,deadline-commits-total:,deadline-commits-per-author:,min-insertions:,null

! PARSED=$(getopt --options=$OPTIONS --longoptions=$LONGOPTS --name "$0" -- "$@")
if [[ ${PIPESTATUS[0]} -ne 0 ]]; then
    # e.g. return value is 1
    # then getopt has complained about wrong arguments to stdout
    exit 2
fi
eval set -- "$PARSED"

branch="main"
min_insertions=4
count_invalid=0
warn_invalid=0
intervals=1
intervals_file="$(readlink -f $(dirname $0))/intervals.txt"
min_commits_per_interval=12
deadline=0
deadline_date=
deadline_commits_total=96
deadline_commits_per_author=24
while true; do
    case "$1" in
        --help)
            usage
            exit 0
            ;;
        --branch)
            branch="$2"
            shift 2
            ;;
        --since)
            since=$(date --date="$2")
            shift 2
            ;;
        --until)
            until=$(date --date="$2")
            shift 2
            ;;
        --intervals)
            intervals=1
            intervals_file="$2"
            if [[ ! -f $intervals_file ]]; then
              >&2 echo "$intervals_file is not a file."
              exit 2
            fi
            shift 2
            ;;
        --min-commits-per-interval)
            min_commits_per_interval="$2"
            shift 2
            ;;
        --deadline)
            deadline=1
            deadline_date=$(date --date="$2")
            shift 2
            ;;
        --deadline-commits-total)
            deadline=1
            deadline_commits_total="$2"
            shift 2
            ;;
        --deadline-commits-per-author)
            deadline=1
            deadline_commits_per_author="$2"
            shift 2
            ;;
        -i|--min-insertions)
            min_insertions="$2"
            shift 2
            ;;
        -c|--count-invalid)
            count_invalid=1
            shift
            ;;
        -w|--warn-invalid)
            warn_invalid=1
            shift
            ;;
        -z|--null)
            nullsep=1
            shift
            ;;
        --)
            shift
            break
            ;;
        *)
            >&2 echo "Programming error"
            exit 3
            ;;
    esac
done

if [[ $# -lt 0 ]]; then
  usage
  exit 2
fi

# if since hasn't been passed as an argument, assume last monday
if [[ -z "$since" ]]; then
  # if today is monday
  if [[ $(date +%u) -eq 1 ]]; then
    since=$(date --date='today')
  else
    since=$(date --date='last monday')
  fi
  since=$(date --date='2019/11/04')
fi
#if until hasn't been passed as an argument, assume next sunday
if [[ -z "$until" ]]; then
  until=$(date --date='23:59:59 sunday')
fi

sincef=$(date --date="$since" +%F)
untilf=$(date --date="$until" +%F)
now=$(date +%s)

if [[ $intervals -eq 1 ]]; then
  intervals_dates=$(cat "$intervals_file")
fi

if [[ $deadline -eq 1 ]]; then
  if [[ -z "$deadline_date" ]]; then
    deadline_date=$(date)
  fi
fi

awkscriptfile="$(readlink -f $(dirname $0))/gitc.awk"

function check-repository() {
  git log "$3" --ignore-all-space --no-color --no-merges --shortstat -z --since="$1" --until="$2" | \
    gawk -f "$awkscriptfile" \
      -v min_insertions="$min_insertions" \
      -v min_commits="$min_commits_per_interval" \
      -v min_commits_per_author="0" \
      -v count_invalid="$count_invalid" -v warn_invalid="$warn_invalid"
}

function check-repository-deadline() {
  git log "$1" --ignore-all-space --no-color --no-merges --shortstat -z --until="$deadline_date" | \
    gawk -f "$awkscriptfile" \
      -v min_insertions="$min_insertions" \
      -v min_commits="$deadline_commits_total" \
      -v min_commits_per_author="$deadline_commits_per_author" \
      -v count_invalid="$count_invalid" -v warn_invalid="$warn_invalid"
}

function print-repository-status() {
  if [[ $1 -ne 0 ]]; then
    echo -e "Repository $path \e[31m NOT ok\e[0m."
  else
    echo -e "Repository $path \e[32mok\e[0m."
  fi
}

paths=$@
#if no repos specified
if [[ -z $paths ]]; then
	# take all folders from current directory
	paths=$(ls -d */)
	printf "Looking at the following repos:\n$paths\n\n"
fi

for path in $paths; do
  if [[ ! -d $path ]]; then
    # assume path is a remote repo to be cloned
	# create repo dir
    dir=$(basename $(dirname $path)__$(basename $path))
	mkdir $dir
    if [[ $? -ne 0 ]]; then
      >&2 echo "Failed to create repository directory."
      exit 3
    fi
    echo "Cloning repository $path into $dir"
    git clone --mirror "$path" "$dir"
    if [[ $? -ne 0 ]]; then
      >&2 echo "Failed to clone repository $path."
      continue
    fi
    pushd $dir > /dev/null 2>&1
  else
    dir=$(readlink -f "$path")
    pushd "$dir" > /dev/null 2>&1
    git rev-parse --git-dir > /dev/null 2>&1
    if [[ $? -ne 0 ]]; then
      >&2 echo "$dir is not a git repository."
      continue
    fi
	git pull
  fi
  # echo "Counting commits since $sincef until $untilf in $dir"
  # basename $(git rev-parse --show-toplevel) # repository name
  if [[ $deadline -eq 1 ]]; then
    echo "### At deadline $deadline_date:"
    check-repository-deadline "$branch"
    print-repository-status $?
  elif [[ $intervals -eq 1 ]]; then
    OLDIFS=$IFS
    IFS=$'\n'
    for interval in $intervals_dates; do
      since=${interval%' '*}
      until=${interval#*' '}
      if [[ $now -lt $since ]]; then
        continue
      fi
	  echo "-- From: $(date -d @$since) To: $(date -d @$until) --"
      check-repository "$since" "$until" "$branch"
	  print-repository-status $?
    done
    IFS="$OLDIFS"
  else
    check-repository "$since" "$until" "$branch"
    print-repository-status $?
  fi
  separator
  popd > /dev/null 2>&1
done
