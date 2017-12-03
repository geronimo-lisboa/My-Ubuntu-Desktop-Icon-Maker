#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <string>
#include <iostream>
#include <fstream>
#include <ios>
#include <QProcess>
#include <QStringList>
#include <algorithm>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
/*
[Desktop Entry]
version=1.0
Type=Application
Terminal=false
Icon=/home/luciano/Downloads/uml-icon.png
Exec=dia
Name=DIA - UML tool
*/

void MainWindow::on_pushButton_clicked()
{
    ////Pega os dados
    std::string nomeInformado = ui->edtNome->text().toUtf8().constData();
    //O nome dado tem que ser melhorado, quero remover os espaços
    std::string nomeDoArquivo = nomeInformado;
    auto l = std::locale{};
    nomeDoArquivo.erase(
    std::remove_if(begin(nomeDoArquivo), end(nomeDoArquivo),[&l](auto ch){
        return std::isspace(ch, l);
    }), nomeDoArquivo.end());

    std::string command = ui->edtComando->text().toUtf8().constData();
    std::string icon = ui->edtIcone->text().toUtf8().constData();
    std::string filepath ="/home/luciano/Desktop/"+nomeDoArquivo+".desktop";
    ////Gera o arquivo
    std::ofstream fileStream = std::ofstream(filepath, std::ios::out);

    fileStream<<std::endl;
    if(!fileStream.is_open())
        throw "nao abriu";
    fileStream<<"[Desktop Entry]"<<std::endl;
    fileStream<<"version=1.0"<<std::endl;
    fileStream<<"Type=Application"<<std::endl;
    fileStream<<"Terminal=false"<<std::endl;
    fileStream<<"Icon="<<icon<<std::endl;
    fileStream<<"Exec="<<command<<std::endl;
    fileStream<<"Name="<<nomeInformado<<std::endl;
    fileStream.close();
    ////altera as permissões
    QProcess process;
    QStringList parametros;
    parametros<<"777";
    parametros<<QString::fromStdString(filepath);
    process.start("chmod", parametros);
    process.waitForFinished();

}
