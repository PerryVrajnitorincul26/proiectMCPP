#include "usermeniu.h"
#include "ui_usermeniu.h"

UserMeniu::UserMeniu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UserMeniu)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);
    //auto wrapperParent = qobject_cast<Wrapper*>(this->parent());
    ui->stackedWidget->insertWidget(1, & _movies);
    connect(&_movies, &MoviesTable::homeClicked,this,&UserMeniu::on_backHome);
    connect(&_signin,&SignIn::Signed,this,&UserMeniu::showUser);
    std::vector<std::string> userLikedGenres;

}

UserMeniu::~UserMeniu()
{
    delete ui;
}

void UserMeniu::on_pushButton_LogOut_clicked() {
  emit logout();

}

void UserMeniu::on_pushButton_showMovieList_clicked() {
    ui->stackedWidget->setCurrentIndex(1);

}

void UserMeniu::on_backHome() {
    ui->stackedWidget->setCurrentIndex(0);

}

void UserMeniu::on_pushButton_sett_clicked() {
ui->stackedWidget->setCurrentIndex(3);
}

void UserMeniu::on_pushButton_recom_clicked() {
ui->stackedWidget->setCurrentIndex(2);
}

void UserMeniu::on_settingsBackButt_clicked() {
    ui->stackedWidget->setCurrentIndex(0);

}

void UserMeniu::on_deleteButton_clicked() {
    auto username = this->currentUser->getUsername();
    auto &db = MovieDatabase::instance();
    auto U = db.getUserByUsername(username);
    int id = U->m_user_id;
    db.deleteAccountById(id);
}

void UserMeniu::on_backButtRec_clicked() {
    ui->stackedWidget->setCurrentIndex(0);

}

void UserMeniu::showUser() {
    auto &dbRef = MovieDatabase::instance();
}

void UserMeniu::setCurrentUser(User *currentUser) {
    UserMeniu::currentUser = currentUser;
    ui->msgLabel->setText("Hello " + QString::fromStdString(this->currentUser->getUsername()) + "!");
}

void UserMeniu::on_likedGenres_pushButton_clicked() {

    if(ui->War->isChecked())
        userLikedGenres.push_back("War");
    if(ui->Action->isChecked())
        userLikedGenres.push_back("Action");
    if(ui->Adventure->isChecked())
        userLikedGenres.push_back("Adventure");
    if(ui->Animation->isChecked())
        userLikedGenres.push_back("Animation");
    if(ui->Children->isChecked())
        userLikedGenres.push_back("Children");
    if(ui->Comedy->isChecked())
        userLikedGenres.push_back("Comedy");
    if(ui->Fantasy->isChecked())
        userLikedGenres.push_back("Fantasy");
    if(ui->Romance->isChecked())
        userLikedGenres.push_back("Romance");
    if(ui->IMAX->isChecked())
        userLikedGenres.push_back("IMAX");
    if(ui->Mystery->isChecked())
        userLikedGenres.push_back("Mystery");
    if(ui->Thriller->isChecked())
        userLikedGenres.push_back("Thriller");
    if(ui->Crime->isChecked())
        userLikedGenres.push_back("Crime");
    if(ui->SciFi->isChecked())
        userLikedGenres.push_back("Sci-Fi");
    if(ui->FilmNoir->isChecked())
        userLikedGenres.push_back("Film-Noir");
    if(ui->Musical->isChecked())
        userLikedGenres.push_back("Musical");
    if(ui->Drama->isChecked())
        userLikedGenres.push_back("Drama");
    if(ui->Horror->isChecked())
        userLikedGenres.push_back("Horror");
    if(ui->Western->isChecked())
        userLikedGenres.push_back("Western");

}






