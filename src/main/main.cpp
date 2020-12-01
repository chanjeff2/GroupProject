#include "mainwindow.h"
#include <iostream>
#include <sstream>
#include <QApplication>

#include <QFile>
#include <QTextStream>
#include <QDir>
#include <QTime>

namespace logging {
	short max_log_files = 5;
	string fileNamePrefix = "log/Debug-";
	string fileSuffix = ".log";
	string timeStringYMD = "%Y-%m-%d";
	string timeStringFileTMDHMS = "%Y-%m-%d_%H：%M：%S"; // colon used here is U+FF1A, not normal literal colon
	string timeStringTMDHMS = "%Y-%m-%d_%H:%M:%S";
	QTextStream *fileStream;
}

const std::string getFormattedTime(string timeFormat) {
	time_t now = time(0);
	struct tm tstruct;
	char buf[80];
	tstruct = *localtime(&now);
	// Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
	// for more information about date/time format
	strftime(buf, sizeof(buf), timeFormat.c_str(), &tstruct);

	return buf;
}

void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
	QByteArray localMsg = msg.toLocal8Bit();
	stringstream ss;
	// with details (file, line, function)
//	if (context.file) {
//		ss << localMsg.constData() << " (" << context.file << ":" << context.line << ", " << context.function << ")\n";
//	} else {
//		ss << localMsg.constData() << '\n';
//	}
	// msg only
	ss << "(" << QTime::currentTime().toString("hh:mm:ss:zzz").toStdString() << ") " << localMsg.constData();

	switch (type) {
		case QtDebugMsg:
		case QtInfoMsg:
			*logging::fileStream << QString::fromStdString(ss.str()) << endl;
			cout << ss.str() << endl;
			break;
		case QtWarningMsg:
		case QtCriticalMsg:
		case QtFatalMsg:
			cerr << ss.str() << endl;
	}
	if (type == QtFatalMsg) {
		abort();
	}
}

int main(int argc, char *argv[])
{
	// logging
    // make dir if not exists
	QDir dir("log");
	if (!dir.exists()) {
		dir.mkdir(".");
	}

    // generate file name
	string fileName = logging::fileNamePrefix + getFormattedTime(logging::timeStringFileTMDHMS) + logging::fileSuffix;

    // check existing number of log files
	QStringList logfiles = dir.entryList(QDir::Files, QDir::Name);
	QTextStream(stdout) << logfiles.size() << " existing log file(s):\n";
	for (auto logfile: logfiles) {
		QTextStream(stdout) << logfile << '\n';
	}
	// remove old log files
	while (logfiles.size() >= logging::max_log_files) {
		QTextStream(stdout) << "deleting oldest log file: " << logfiles.first() << "\n";
		dir.remove(logfiles.first());
		logfiles.pop_front();
	}

    // generate log file
	QFile file(fileName.c_str());
	file.open(QIODevice::Append|QIODevice::WriteOnly);
	logging::fileStream = new QTextStream(&file);

	QFileInfo fi(file);
	QTextStream(stdout) << "new log file path: " << fi.absoluteFilePath() << '\n';

	const string timeStamp = getFormattedTime(logging::timeStringTMDHMS);

	*logging::fileStream << "<log-" << timeStamp.c_str() << ">" << endl;

	qInstallMessageHandler(myMessageOutput);
	// end of logging

	QApplication a(argc, argv);
	MainWindow w;
	w.show();
	auto result = a.exec();
	*logging::fileStream << "</log-" << timeStamp.c_str() << ">" << endl;
	file.close();
	return result;
}
