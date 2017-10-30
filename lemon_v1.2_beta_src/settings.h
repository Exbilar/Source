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

#ifndef SETTINGS_H
#define SETTINGS_H

#include <QtCore>
#include <QObject>

class Compiler;

class Settings : public QObject
{
    Q_OBJECT
public:
    explicit Settings(QObject *parent = 0);
    
    int getDefaultFullScore() const;
    int getDefaultTimeLimit() const;
    int getDefaultMemoryLimit() const;
    int getCompileTimeLimit() const;
    int getSpecialJudgeTimeLimit() const;
    int getFileSizeLimit() const;
    int getNumberOfThreads() const;
    const QString& getDefaultInputFileExtension() const;
    const QString& getDefaultOutputFileExtension() const;
    const QStringList& getInputFileExtensions() const;
    const QStringList& getOutputFileExtensions() const;
    const QStringList& getRecentContest() const;
    const QList<Compiler*>& getCompilerList() const;
    const QString& getUiLanguage() const;
    const QString& getDiffPath() const;
    
    void setDefaultFullScore(int);
    void setDefaultTimeLimit(int);
    void setDefaultMemoryLimit(int);
    void setCompileTimeLimit(int);
    void setSpecialJudgeTimeLimit(int);
    void setFileSizeLimit(int);
    void setNumberOfThreads(int);
    void setDefaultInputFileExtension(const QString&);
    void setDefaultOutputFileExtension(const QString&);
    void setInputFileExtensions(const QString&);
    void setOutputFileExtensions(const QString&);
    void setRecentContest(const QStringList&);
    void setUiLanguage(const QString&);
    
    void addCompiler(Compiler*);
    void deleteCompiler(int);
    Compiler* getCompiler(int);
    void swapCompiler(int, int);
    void copyFrom(Settings*);
    void saveSettings();
    void loadSettings();
    
    static int upperBoundForFullScore();
    static int upperBoundForTimeLimit();
    static int upperBoundForMemoryLimit();
    static int upperBoundForFileSizeLimit();
    static int upperBoundForNumberOfThreads();
    static QString dataPath();
    static QString sourcePath();
    static QString temporaryPath();
    static QString selfTestPath();

private:
    QList<Compiler*> compilerList;
    int defaultFullScore;
    int defaultTimeLimit;
    int defaultMemoryLimit;
    int compileTimeLimit;
    int specialJudgeTimeLimit;
    int fileSizeLimit;
    int numberOfThreads;
    QString defaultInputFileExtension;
    QString defaultOutputFileExtension;
    QStringList inputFileExtensions;
    QStringList outputFileExtensions;
    QStringList recentContest;
    QString uiLanguage;
    QString diffPath;
};

#endif // SETTINGS_H
