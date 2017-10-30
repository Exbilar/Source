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

#include "detaildialog.h"
#include "ui_detaildialog.h"
#include "task.h"
#include "testcase.h"
#include "contest.h"
#include "contestant.h"
#include "globaltype.h"
#include "judgingdialog.h"

DetailDialog::DetailDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DetailDialog)
{
    ui->setupUi(this);
    connect(ui->detailViewer, SIGNAL(anchorClicked(QUrl)),
            this, SLOT(anchorClicked(QUrl)));
}

DetailDialog::~DetailDialog()
{
    delete ui;
}

void DetailDialog::refreshViewer(Contest *_contest, Contestant *_contestant)
{
    contest = _contest;
    contestant = _contestant;
    
    setWindowTitle(tr("Contestant: %1").arg(contestant->getContestantName()));
    ui->detailViewer->clear();
    QString htmlCode;
    
    htmlCode += "<html><head>";
    htmlCode += "<style type=\"text/css\">th, td {padding-left: 1em; padding-right: 1em;}</style>";
    htmlCode += "</head><body>";
    
    QList<Task*> taskList = contest->getTaskList();
    for (int i = 0; i < taskList.size(); i ++) {
        htmlCode += "<p><span style=\"font-weight:bold; font-size:large;\">";
        htmlCode += QString("%1 %2 <a href=\"Rejudge %3\" style=\"text-decoration: none\">(%4)</span><br>")
                    .arg(tr("Task")).arg(taskList[i]->getProblemTile()).arg(i).arg(tr("Rejudge"));
        
        if (! contestant->getCheckJudged(i)) {
            htmlCode += QString("&nbsp;&nbsp;%1</p>").arg(tr("Not judged"));
            continue;
        }
        
        if (taskList[i]->getTaskType() == Task::Traditional) {
            if (contestant->getCompileState(i) != CompileSuccessfully) {
                switch (contestant->getCompileState(i)) {
                    case NoValidSourceFile:
                        htmlCode += QString("&nbsp;&nbsp;%1</p>").arg(tr("Cannot find valid source file"));
                        break;
                    case CompileTimeLimitExceeded:
                        htmlCode += QString("&nbsp;&nbsp;%1%2<br>").arg(tr("Source file: ")).arg(contestant->getSourceFile(i));
                        htmlCode += QString("&nbsp;&nbsp;%1</p>").arg(tr("Compile time limit exceeded"));
                        break;
                    case InvalidCompiler:
                        htmlCode += QString("&nbsp;&nbsp;%1</p>").arg(tr("Cannot run given compiler"));
                        break;
                    case CompileError:
                        htmlCode += QString("&nbsp;&nbsp;%1%2<br>").arg(tr("Source file: ")).arg(contestant->getSourceFile(i));
                        htmlCode += QString("&nbsp;&nbsp;%1").arg(tr("Compile error"));
                        if (! contestant->getCompileMessage(i).isEmpty())
                            htmlCode += QString("<a href=\"CompileMessage %1\" style=\"text-decoration: none\"> (...)").arg(i);
                        htmlCode += "</p>";
                        break;
                }
                continue;
            }
            htmlCode += QString("&nbsp;&nbsp;%1%2").arg(tr("Source file: ")).arg(contestant->getSourceFile(i));
        }
        
        htmlCode += "<table width=\"100%\" border=\"1\" cellpadding=\"1\"><tr>";
        htmlCode += QString("<th scope=\"col\" nowrap=\"nowrap\">%1</th>").arg(tr("Test Case"));
        htmlCode += QString("<th scope=\"col\" nowrap=\"nowrap\">%1</th>").arg(tr("Input File"));
        htmlCode += QString("<th scope=\"col\">%1</th>").arg(tr("Result"));
        htmlCode += QString("<th scope=\"col\" nowrap=\"nowrap\">%1</th>").arg(tr("Time Used"));
        htmlCode += QString("<th scope=\"col\" nowrap=\"nowrap\">%1</th>").arg(tr("Memory Used"));
        htmlCode += QString("<th scope=\"col\" nowrap=\"nowrap\">%1</th></tr>").arg(tr("Score"));
        
        QList<QStringList> inputFiles = contestant->getInputFiles(i);
        QList< QList<ResultState> > result = contestant->getResult(i);
        QList<QStringList> message = contestant->getMessage(i);
        QList< QList<int> > timeUsed = contestant->getTimeUsed(i);
        QList< QList<int> > memoryUsed = contestant->getMemoryUsed(i);
        QList< QList<int> > score = contestant->getSocre(i);
        
        for (int j = 0; j < inputFiles.size(); j ++) {
            for (int k = 0; k < inputFiles[j].size(); k ++) {
                htmlCode += "<tr>";
                if (k == 0) {
                    htmlCode += QString("<td nowrap=\"nowrap\" rowspan=\"%1\" align=\"center\" valign=\"middle\">#%2</td>")
                                .arg(inputFiles[j].size()).arg(j + 1);
                }
                
                htmlCode += QString("<td nowrap=\"nowrap\" align=\"center\">%1</td>").arg(inputFiles[j][k]);
                
                QString text;
                switch (result[j][k]) {
                    case CorrectAnswer:
                        text = tr("Correct Answer");
                        break;
                    case WrongAnswer:
                        text = tr("Wrong Answer");
                        break;
                    case PartlyCorrect:
                        text = tr("Partly Correct");
                        break;
                    case TimeLimitExceeded:
                        text = tr("Time Limit Exceeded");
                        break;
                    case MemoryLimitExceeded:
                        text = tr("Memory Limit Exceeded");
                        break;
                    case CannotStartProgram:
                        text = tr("Cannot Start Program");
                        break;
                    case FileError:
                        text = tr("File Error");
                        break;
                    case RunTimeError:
                        text = tr("Run Time Error");
                        break;
                    case InvalidSpecialJudge:
                        text = tr("Invalid Special Judge");
                        break;
                    case SpecialJudgeTimeLimitExceeded:
                        text = tr("Special Judge Time Limit Exceeded");
                        break;
                    case SpecialJudgeRunTimeError:
                        text = tr("Special Judge Run Time Error");
                        break;
                }
                
                htmlCode += QString("<td align=\"center\">%1").arg(text);
                if (! message[j][k].isEmpty()) {
                    htmlCode += QString("<a href=\"Message %1 %2 %3\" style=\"text-decoration: none\"> (...)</a>").arg(i).arg(j).arg(k);
                }
                htmlCode += "</td>";
                
                htmlCode += "<td nowrap=\"nowrap\" align=\"center\">";
                if (timeUsed[j][k] != -1) {
                    htmlCode += QString("").sprintf("%.3lf s", double(timeUsed[j][k]) / 1000);
                } else {
                    htmlCode += tr("Invalid");
                }
                htmlCode += "</td>";
                
                htmlCode += "<td nowrap=\"nowrap\" align=\"center\">";
                if (memoryUsed[j][k] != -1) {
                    htmlCode += QString("").sprintf("%.3lf MB", double(memoryUsed[j][k]) / 1024 / 1024);
                } else {
                    htmlCode += tr("Invalid");
                }
                htmlCode += "</td>";
                
                if (k == 0) {
                    htmlCode += QString("<td rowspan=\"%1\" align=\"center\" valign=\"middle\">").arg(inputFiles[j].size());
                    int minv = 1000000000;
                    for (int t = 0; t < inputFiles[j].size(); t ++)
                        if (score[j][t] < minv) minv = score[j][t];
                    htmlCode += QString("%1</td>").arg(minv);
                }
                
                htmlCode += "</tr>";
            }
        }
        
        htmlCode += "</table><br></p>";
    }
    
    htmlCode += "</body></html>";
    ui->detailViewer->setHtml(htmlCode);
}

void DetailDialog::showDialog()
{
    show();
    QScrollBar *bar = ui->detailViewer->verticalScrollBar();
    bar->setValue(bar->minimum());
    bar = ui->detailViewer->horizontalScrollBar();
    bar->setValue(bar->minimum());
    exec();
}

void DetailDialog::anchorClicked(const QUrl &url)
{
    QStringList list = url.path().split(' ', QString::SkipEmptyParts);
    
    if (list[0] == "Rejudge") {
        JudgingDialog *dialog = new JudgingDialog(this);
        dialog->setModal(true);
        dialog->setContest(contest);
        dialog->show();
        dialog->judge(contestant->getContestantName(), list[1].toInt());
        delete dialog;
        emit rejudgeSignal();
        refreshViewer(contest, contestant);
    }
    
    if (list[0] == "CompileMessage") {
        QMessageBox(QMessageBox::NoIcon, tr("Compile Message"),
                    QString("<code>%1</code>").arg(contestant->getCompileMessage(list[1].toInt())),
                    QMessageBox::Close, this).exec();
    }
    
    if (list[0] == "Message") {
        QList<QStringList> message = contestant->getMessage(list[1].toInt());
        QMessageBox(QMessageBox::NoIcon, tr("Message"),
                    QString("<code>%1</code>").arg(message[list[2].toInt()][list[3].toInt()]),
                    QMessageBox::Close, this).exec();
    }
}
