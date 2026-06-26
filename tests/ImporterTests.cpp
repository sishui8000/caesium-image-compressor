#include "ImporterTests.h"

#include <services/Importer.h>
#include <QFile>
#include <QTemporaryDir>

ImporterTests::ImporterTests()
= default;
ImporterTests::~ImporterTests()
= default;

void ImporterTests::initTestCase()
{
    Q_ASSERT(true);
}

void ImporterTests::cleanupTestCase()
{
    Q_ASSERT(true);
}

void ImporterTests::rootFolderTestCase()
{
    QStringList folderMap = QStringList() << "/";
    QString rootFolder = Importer::getRootFolder(folderMap);
    Q_ASSERT(rootFolder == QString("/"));

    folderMap = QStringList() << "/1" << "/1/1-1";
    rootFolder = Importer::getRootFolder(folderMap);
    Q_ASSERT(rootFolder == QString("/1"));

    folderMap = QStringList() << "/1/1-1" << "/1/1-2";
    rootFolder = Importer::getRootFolder(folderMap);
    Q_ASSERT(rootFolder == QString("/1"));

    folderMap = QStringList() << "/1/1-1" << "/1/1-2";
    rootFolder = Importer::getRootFolder(folderMap);
    Q_ASSERT(rootFolder == QString("/1"));
}

void ImporterTests::scanDirectoryIncludesBmpTestCase()
{
    QTemporaryDir temporaryDir;
    Q_ASSERT(temporaryDir.isValid());

    QFile bmpFile(temporaryDir.filePath("image.bmp"));
    Q_ASSERT(bmpFile.open(QIODevice::WriteOnly));
    bmpFile.close();

    QFile ignoredFile(temporaryDir.filePath("image.txt"));
    Q_ASSERT(ignoredFile.open(QIODevice::WriteOnly));
    ignoredFile.close();

    QStringList files = Importer::scanDirectory(temporaryDir.path(), false);

    Q_ASSERT(files.contains(bmpFile.fileName()));
    Q_ASSERT(!files.contains(ignoredFile.fileName()));
}
