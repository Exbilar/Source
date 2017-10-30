/***************************************************************************
    This file is part of Project Lemon
    Copyright (C) 2011 Zhipeng Jia

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
***************************************************************************/

#include "lemon.h"
#include "ui_lemon.h"
#include "task.h"
#include "testcase.h"
#include "contest.h"
#include "compiler.h"
#include "contestant.h"
#include "settings.h"
#include "optionsdialog.h"
#include "addcompilerwizard.h"
#include "newcontestdialog.h"
#include "opencontestdialog.h"
#include "welcomedialog.h"
#include "addtaskdialog.h"
#include "detaildialog.h"
#include "selftestutil.h"
#include "exportutil.h"

Lemon::Lemon(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Lemon)
{
    ui->setupUi(this);
    
    curContest = 0;
    settings = new Settings(this);
    
    ui->tabWidget->setVisible(false);
    ui->closeAction->setEnabled(false);
    
    dataDirWatcher = 0;
    settings->loadSettings();
    
    ui->summary->setSettings(settings);
    ui->taskEdit->setSettings(settings);
    ui->testCaseEdit->setSettings(settings);
    
    connect(this, SIGNAL(dataPathChanged()),
            ui->taskEdit, SIGNAL(dataPathChanged()));
    connect(this, SIGNAL(dataPathChanged()),
            ui->testCaseEdit, SIGNAL(dataPathChanged()));
    
    connect(ui->summary, SIGNAL(currentItemChanged(QTreeWidgetItem*,QTreeWidgetItem*)),
            this, SLOT(summarySelectionChanged()));
    connect(ui->optionsAction, SIGNAL(triggered()),
            this, SLOT(showOptionsDialog()));
    connect(ui->refreshButton, SIGNAL(clicked()),
            this, SLOT(refreshButtonClicked()));
    connect(ui->judgeButton, SIGNAL(clicked()),
            ui->resultViewer, SLOT(judgeSelected()));
    connect(ui->judgeAllButton, SIGNAL(clicked()),
            ui->resultViewer, SLOT(judgeAll()));
    connect(ui->judgeAction, SIGNAL(triggered()),
            ui->resultViewer, SLOT(judgeSelected()));
    connect(ui->judgeAllAction, SIGNAL(triggered()),
            ui->resultViewer, SLOT(judgeAll()));
    connect(ui->tabWidget, SIGNAL(currentChanged(int)),
            this, SLOT(tabIndexChanged(int)));
    connect(ui->resultViewer, SIGNAL(itemSelectionChanged()),
            this, SLOT(viewerSelectionChanged()));
    connect(ui->resultViewer, SIGNAL(contestantDeleted()),
            this, SLOT(contestantDeleted()));
    connect(ui->newAction, SIGNAL(triggered()),
            this, SLOT(newAction()));
    connect(ui->openAction, SIGNAL(triggered()),
            this, SLOT(loadAction()));
    connect(ui->closeAction, SIGNAL(triggered()),
            this, SLOT(closeAction()));
    connect(ui->addTasksAction, SIGNAL(triggered()),
            this, SLOT(addTasksAction()));
    connect(ui->makeSelfTestAction, SIGNAL(triggered()),
            this, SLOT(makeSelfTest()));
    connect(ui->exportAction, SIGNAL(triggered()),
            this, SLOT(exportResult()));
    connect(ui->aboutAction, SIGNAL(triggered()),
            this, SLOT(aboutLemon()));
    connect(ui->exitAction, SIGNAL(triggered()),
            this, SLOT(close()));
    
    appTranslator = new QTranslator(this);
    qtTranslator = new QTranslator(this);
    QApplication::installTranslator(appTranslator);
    QApplication::installTranslator(qtTranslator);
    
    QStringList fileList = QDir(":/translation").entryList(QStringList() << "lemon_*.qm", QDir::Files);
    for (int i = 0; i < fileList.size(); i ++) {
        appTranslator->load(QString(":/translation/%1").arg(fileList[i]));
        QAction *newLanguage = new QAction(appTranslator->translate("Lemon", "English"), this);
        newLanguage->setCheckable(true);
        QString language = QFileInfo(fileList[i]).baseName();
        language.remove(0, language.indexOf('_') + 1);
        newLanguage->setData(language);
        connect(newLanguage, SIGNAL(triggered()),
                this, SLOT(setUiLanguage()));
        languageActions.append(newLanguage);
    }
    ui->languageMenu->addActions(languageActions);
    ui->setEnglishAction->setData("en");
    ui->setEnglishAction->setCheckable(true);
    connect(ui->setEnglishAction, SIGNAL(triggered()),
            this, SLOT(setUiLanguage()));
    loadUiLanguage();
    
    QSettings settings("Crash", "Lemon");
    QSize _size = settings.value("WindowSize", size()).toSize();
    resize(_size);
}

Lemon::~Lemon()
{
    delete ui;
}

void Lemon::changeEvent(QEvent *event)
{
    if (event->type() == QEvent::LanguageChange) {
        ui->retranslateUi(this);
        ui->resultViewer->refreshViewer();
    }
}

void Lemon::closeEvent(QCloseEvent *event)
{
    if (curContest) saveContest(curFile);
    settings->saveSettings();
    QSettings settings("Crash", "Lemon");
    settings.setValue("WindowSize", size());
}

void Lemon::welcome()
{
    if (settings->getCompilerList().size() == 0) {
        AddCompilerWizard *wizard = new AddCompilerWizard(this);
        if (wizard->exec() == QDialog::Accepted) {
            QList<Compiler*> compilerList = wizard->getCompilerList();
            for (int i = 0; i < compilerList.size(); i ++)
                settings->addCompiler(compilerList[i]);
        }
        delete wizard;
    }
    
    WelcomeDialog *dialog = new WelcomeDialog(this);
    dialog->setRecentContest(settings->getRecentContest());
    if (dialog->exec() == QDialog::Accepted) {
        settings->setRecentContest(dialog->getRecentContest());
        if (dialog->getCurrentTab() == 0) {
            loadContest(dialog->getSelectedContest());
        } else {
            newContest(dialog->getContestTitle(), dialog->getSavingName(), dialog->getContestPath());
        }
    } else {
        settings->setRecentContest(dialog->getRecentContest());
    }
    delete dialog;
}

void Lemon::loadUiLanguage()
{
    ui->setEnglishAction->setChecked(false);
    for (int i = 0; i < languageActions.size(); i ++) {
        languageActions[i]->setChecked(false);
    }
    for (int i = 0; i < languageActions.size(); i ++) {
        if (languageActions[i]->data().toString() == settings->getUiLanguage()) {
            languageActions[i]->setChecked(true);
            appTranslator->load(QString(":/translation/lemon_%1.qm").arg(settings->getUiLanguage()));
            qtTranslator->load(QString(":/translation/qt_%1.qm").arg(settings->getUiLanguage()));
            return;
        }
    }
    settings->setUiLanguage("en");
    appTranslator->load("");
    qtTranslator->load("");
    ui->setEnglishAction->setChecked(true);
}

void Lemon::insertWatchPath(const QString &curDir, QFileSystemWatcher *watcher)
{
    watcher->addPath(curDir);
    QDir dir(curDir);
    QStringList list = dir.entryList(QDir::AllDirs | QDir::NoDotAndDotDot);
    for (int i = 0; i < list.size(); i ++) {
        insertWatchPath(curDir + list[i] + QDir::separator(), watcher);
    }
}

void Lemon::resetDataWatcher()
{
    if (dataDirWatcher) delete dataDirWatcher;
    dataDirWatcher = new QFileSystemWatcher(this);
    insertWatchPath(Settings::dataPath(), dataDirWatcher);
    connect(dataDirWatcher, SIGNAL(directoryChanged(QString)),
            this, SLOT(resetDataWatcher()));
    connect(dataDirWatcher, SIGNAL(fileChanged(QString)),
            this, SIGNAL(dataPathChanged()));
    connect(dataDirWatcher, SIGNAL(directoryChanged(QString)),
            this, SIGNAL(dataPathChanged()));
    emit dataPathChanged();
}

void Lemon::summarySelectionChanged()
{
    if (! ui->summary->isEnabled()) return;
    
    QTreeWidgetItem *curItem = ui->summary->currentItem();
    if (! curItem) {
        ui->taskEdit->setEditTask(0);
        ui->editWidget->setCurrentIndex(0);
        return;
    }
    
    int index = ui->summary->indexOfTopLevelItem(curItem);
    if (index != -1) {
        ui->taskEdit->setEditTask(curContest->getTask(index));
        ui->editWidget->setCurrentIndex(1);
    } else {
        QTreeWidgetItem *parentItem = curItem->parent();
        int taskIndex = ui->summary->indexOfTopLevelItem(parentItem);
        int testCaseIndex = parentItem->indexOfChild(curItem);
        Task *curTask = curContest->getTask(taskIndex);
        TestCase *curTestCase = curTask->getTestCase(testCaseIndex);
        ui->testCaseEdit->setEditTestCase(curTestCase, curTask->getTaskType() == Task::Traditional);
        ui->editWidget->setCurrentIndex(2);
    }
}

void Lemon::showOptionsDialog()
{
    OptionsDialog *dialog = new OptionsDialog(this);
    dialog->resetEditSettings(settings);
    if (dialog->exec() == QDialog::Accepted) {
        settings->copyFrom(dialog->getEditSettings());
        ui->testCaseEdit->setSettings(settings);
        if (curContest) {
            const QList<Task*> &taskList = curContest->getTaskList();
            for (int i = 0; i < taskList.size(); i ++)
                taskList[i]->refreshCompilerConfiguration(settings);
        }
    }
    delete dialog;
}

void Lemon::refreshButtonClicked()
{
    curContest->refreshContestantList();
    ui->resultViewer->refreshViewer();
    if (ui->resultViewer->rowCount() > 0) {
        ui->judgeAllButton->setEnabled(true);
        ui->judgeAllAction->setEnabled(true);
    } else {
        ui->judgeAllButton->setEnabled(false);
        ui->judgeAllAction->setEnabled(false);
    }
}

void Lemon::tabIndexChanged(int index)
{
    if (index == 0) {
        ui->judgeAction->setEnabled(false);
        ui->judgeButton->setEnabled(false);
        ui->judgeAllAction->setEnabled(false);
        ui->judgeAllButton->setEnabled(false);
    } else {
        QList<QTableWidgetSelectionRange> selectionRange = ui->resultViewer->selectedRanges();
        if (selectionRange.size() > 0) {
            ui->judgeAction->setEnabled(true);
            ui->judgeButton->setEnabled(true);
        } else {
            ui->judgeAction->setEnabled(false);
            ui->judgeButton->setEnabled(false);
        }
        if (ui->resultViewer->rowCount() > 0) {
            ui->judgeAllAction->setEnabled(true);
            ui->judgeAllButton->setEnabled(true);
        } else {
            ui->judgeAllAction->setEnabled(false);
            ui->judgeAllButton->setEnabled(false);
        }
    }
}

void Lemon::viewerSelectionChanged()
{
    QList<QTableWidgetSelectionRange> selectionRange = ui->resultViewer->selectedRanges();
    if (selectionRange.size() > 0) {
        ui->judgeButton->setEnabled(true);
        ui->judgeAction->setEnabled(true);
    } else {
        ui->judgeButton->setEnabled(false);
        ui->judgeAction->setEnabled(false);
    }
}

void Lemon::contestantDeleted()
{
    if (ui->resultViewer->rowCount() > 0) {
        ui->judgeAllButton->setEnabled(true);
        ui->judgeAllAction->setEnabled(true);
    } else {
        ui->judgeAllButton->setEnabled(false);
        ui->judgeAllAction->setEnabled(false);
    }
}

void Lemon::saveContest(const QString &fileName)
{
    QFile file(fileName);
    if (! file.open(QFile::WriteOnly)) {
        QMessageBox::warning(this, tr("Error"), tr("Cannot open file %1").arg(fileName),
                             QMessageBox::Close);
        return;
    }
    
    QApplication::setOverrideCursor(Qt::WaitCursor);
    
    QByteArray data;
    QDataStream _out(&data, QIODevice::WriteOnly);
    curContest->writeToStream(_out);
    data = qCompress(data);
    QDataStream out(&file);
    out << unsigned(MagicNumber) << qChecksum(data.data(), data.length()) << data.length();
    out.writeRawData(data.data(), data.length());
    
    QApplication::restoreOverrideCursor();
}

void Lemon::loadContest(const QString &filePath)
{
    if (curContest) closeAction();
    
    QFile file(filePath);
    if (! file.open(QFile::ReadOnly)) {
        QMessageBox::warning(this, tr("Error"), tr("Cannot open file %1").arg(QFileInfo(filePath).fileName()),
                             QMessageBox::Close);
        return;
    }
    
    QDataStream _in(&file);
    unsigned checkNumber;
    _in >> checkNumber;
    if (checkNumber != unsigned(MagicNumber)) {
        QMessageBox::warning(this, tr("Error"), tr("File %1 is broken").arg(QFileInfo(filePath).fileName()),
                             QMessageBox::Close);
        return;
    }
    
    quint16 checksum;
    int len;
    _in >> checksum >> len;
    char *raw = new char[len];
    _in.readRawData(raw, len);
    if (qChecksum(raw, len) != checksum) {
        QMessageBox::warning(this, tr("Error"), tr("File %1 is broken").arg(QFileInfo(filePath).fileName()),
                             QMessageBox::Close);
        delete[] raw;
        return;
    }
    
    QByteArray data(raw, len);
    delete[] raw;
    data = qUncompress(data);
    QDataStream in(data);
    
    QApplication::setOverrideCursor(Qt::WaitCursor);
    
    curContest = new Contest(this);
    curContest->setSettings(settings);
    curContest->readFromStream(in);
    
    curFile = QFileInfo(filePath).fileName();
    QDir::setCurrent(QFileInfo(filePath).path());
    QDir().mkdir(Settings::dataPath());
    QDir().mkdir(Settings::sourcePath());
    ui->summary->setContest(curContest);
    ui->resultViewer->setContest(curContest);
    ui->resultViewer->refreshViewer();
    ui->tabWidget->setVisible(true);
    resetDataWatcher();
    ui->closeAction->setEnabled(true);
    ui->addTasksAction->setEnabled(true);
    ui->makeSelfTestAction->setEnabled(true);
    ui->exportAction->setEnabled(true);
    setWindowTitle(tr("Lemon - %1").arg(curContest->getContestTitle()));
    
    QApplication::restoreOverrideCursor();
    ui->tabWidget->setCurrentIndex(0);
}

void Lemon::newContest(const QString &title, const QString &savingName, const QString &path)
{
    if (! QDir(path).exists() && ! QDir().mkpath(path)) {
        QMessageBox::warning(this, tr("Error"), tr("Cannot make contest path"),
                             QMessageBox::Close);
        return;
    }
    
    if (curContest) closeAction();
    curContest = new Contest(this);
    curContest->setSettings(settings);
    curContest->setContestTitle(title);
    setWindowTitle(tr("Lemon - %1").arg(title));
    QDir::setCurrent(path);
    QDir().mkdir(Settings::dataPath());
    QDir().mkdir(Settings::sourcePath());
    curFile = savingName + ".cdf";
    saveContest(curFile);
    ui->summary->setContest(curContest);
    ui->resultViewer->setContest(curContest);
    ui->resultViewer->refreshViewer();
    ui->tabWidget->setVisible(true);
    resetDataWatcher();
    ui->closeAction->setEnabled(true);
    ui->addTasksAction->setEnabled(true);
    ui->makeSelfTestAction->setEnabled(true);
    ui->exportAction->setEnabled(true);
    QStringList recentContest = settings->getRecentContest();
    recentContest.append(QDir::toNativeSeparators((QDir().absoluteFilePath(curFile))));
    settings->setRecentContest(recentContest);
    ui->tabWidget->setCurrentIndex(0);
}

void Lemon::newAction()
{
    NewContestDialog *dialog = new NewContestDialog(this);
    if (dialog->exec() == QDialog::Accepted) {
        newContest(dialog->getContestTitle(), dialog->getSavingName(), dialog->getContestPath());
    }
    delete dialog;
}

void Lemon::closeAction()
{
    saveContest(curFile);
    ui->summary->setContest(0);
    ui->taskEdit->setEditTask(0);
    ui->resultViewer->setContest(0);
    delete curContest;
    curContest = 0;
    ui->tabWidget->setCurrentIndex(0);
    ui->tabWidget->setVisible(false);
    ui->closeAction->setEnabled(false);
    ui->addTasksAction->setEnabled(false);
    ui->makeSelfTestAction->setEnabled(false);
    ui->exportAction->setEnabled(false);
    setWindowTitle(tr("Lemon"));
}

void Lemon::loadAction()
{
    OpenContestDialog *dialog = new OpenContestDialog(this);
    dialog->setRecentContest(settings->getRecentContest());
    QStringList recentContest = dialog->getRecentContest();
    if (dialog->exec() == QDialog::Accepted) {
        QString selectedContest = dialog->getSelectedContest();
        for (int i = 0; i < recentContest.size(); i ++) {
            if (recentContest[i] == selectedContest) {
                recentContest.removeAt(i);
                break;
            }
        }
        recentContest.prepend(selectedContest);
        loadContest(selectedContest);
    }
    settings->setRecentContest(recentContest);
    delete dialog;
}

void Lemon::getFiles(const QString &path, const QStringList &filters, QMap<QString, QString> &files)
{
    QDir dir(path);
    if (! filters.isEmpty()) dir.setNameFilters(filters);
    QFileInfoList list = dir.entryInfoList(QDir::Files);
    for (int i = 0; i < list.size(); i ++) {
        files.insert(list[i].completeBaseName(), list[i].fileName());
    }
}

void Lemon::addTask(const QString &title, const QList<QPair<QString, QString> > &testCases,
                    int fullScore, int timeLimit, int memoryLimit)
{
    Task *newTask = new Task;
    newTask->setProblemTitle(title);
    newTask->setSourceFileName(title);
    newTask->setInputFileName(title + ".in");
    newTask->setOutputFileName(title + ".out");
    newTask->refreshCompilerConfiguration(settings);
    newTask->setAnswerFileExtension(settings->getDefaultOutputFileExtension());
    curContest->addTask(newTask);
    for (int i = 0; i < testCases.size(); i ++) {
        TestCase *newTestCase = new TestCase;
        newTestCase->setFullScore(fullScore);
        newTestCase->setTimeLimit(timeLimit);
        newTestCase->setMemoryLimit(memoryLimit);
        newTestCase->addSingleCase(title + QDir::separator() + testCases[i].first,
                                   title + QDir::separator() + testCases[i].second);
        newTask->addTestCase(newTestCase);
    }
}

bool Lemon::compareFileName(const QPair<QString, QString> &a, const QPair<QString, QString> &b)
{
    return a.first.length() < b.first.length()
            || a.first.length() == b.first.length() && QString::localeAwareCompare(a.first, b.first) < 0;
}

void Lemon::addTasksAction()
{
    QStringList list = QDir(Settings::dataPath()).entryList(QDir::Dirs | QDir::NoDotAndDotDot);
    QSet<QString> nameSet;
    QList<Task*> taskList = curContest->getTaskList();
    for (int i = 0; i < taskList.size(); i ++) {
        nameSet.insert(taskList[i]->getSourceFileName());
    }
    QStringList nameList;
    QList< QList< QPair<QString, QString> > > testCases;
    for (int i = 0; i < list.size(); i ++) {
        if (! nameSet.contains(list[i])) {
            QStringList filters;
            filters = settings->getInputFileExtensions();
            if (filters.isEmpty()) filters << "in";
            for (int j = 0; j < filters.size(); j ++) {
                filters[j] = QString("*.") + filters[j];
            }
            QMap<QString, QString> inputFiles;
            getFiles(Settings::dataPath() + list[i], filters, inputFiles);
            
            filters = settings->getOutputFileExtensions();
            if (filters.isEmpty()) filters << "out" << "ans";
            for (int j = 0; j < filters.size(); j ++) {
                filters[j] = QString("*.") + filters[j];
            }
            QMap<QString, QString> outputFiles;
            getFiles(Settings::dataPath() + list[i], filters, outputFiles);
            
            QList< QPair<QString, QString> > cases;
            QStringList baseNameList = inputFiles.keys();
            for (int j = 0; j < baseNameList.size(); j ++) {
                if (outputFiles.contains(baseNameList[j])) {
                    cases.append(qMakePair(inputFiles[baseNameList[j]], outputFiles[baseNameList[j]]));
                }
            }
            
            qSort(cases.begin(), cases.end(), compareFileName);
            if (! cases.isEmpty()) {
                nameList.append(list[i]);
                testCases.append(cases);
            }
        }
    }
    
    if (nameList.isEmpty()) {
        QMessageBox::warning(this, tr("Lemon"), tr("No task found"), QMessageBox::Ok);
        return;
    }
    
    AddTaskDialog *dialog = new AddTaskDialog(this);
    dialog->resize(dialog->sizeHint());
    dialog->setMaximumSize(dialog->sizeHint());
    dialog->setMinimumSize(dialog->sizeHint());
    for (int i = 0; i < nameList.size(); i ++) {
        dialog->addTask(nameList[i], 100, settings->getDefaultTimeLimit(), settings->getDefaultMemoryLimit());
    }
    if (dialog->exec() == QDialog::Accepted) {
        for (int i = 0; i < nameList.size(); i ++) {
            addTask(nameList[i], testCases[i], dialog->getFullScore(i) / testCases[i].size(),
                    dialog->getTimeLimit(i), dialog->getMemoryLimit(i));
        }
    }
    
    ui->summary->setContest(curContest);
}

void Lemon::makeSelfTest()
{
    SelfTestUtil::makeSelfTest(this, curContest);
}

void Lemon::exportResult()
{
    ExportUtil::exportResult(this, curContest);
}

void Lemon::aboutLemon()
{
    QString text;
    text += "<h2>Project Lemon</h2>";
    text += tr("A tiny judging environment for OI contest") + "<br>";
    text += tr("Version 1.2 Beta") + "<br>";
    text += tr("Build Date: %1").arg(__DATE__) + "<br>";
    text += tr("Copyright (c) 2011 Zhipeng Jia") + "<br>";
    text += tr("This program is under the <a href=\"http://www.gnu.org/licenses/gpl-3.0.html\">GPLv3</a> license")
            + "<br>";
    text += QString("<a href=\"http://hi.baidu.com/oimaster\">") + tr("Author\'s blog") + "</a><br>";
    text += QString("<a href=\"http://code.google.com/p/project-lemon\">") + tr("Google Code Page") + "</a>";
    QMessageBox::about(this, tr("About Lemon"), text);
}

void Lemon::setUiLanguage()
{
    QAction *language = dynamic_cast<QAction*>(sender());
    settings->setUiLanguage(language->data().toString());
    loadUiLanguage();
}
