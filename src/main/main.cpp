#include "mainwindow.h"
#include <iostream>
#include <sstream>
#include <QApplication>

#include <QFile>
#include <QTextStream>
#include <QDir>

namespace logging {
	string fileNamePrefix = "log/Debug-";
	string fileSuffix = ".log";
	string timeStringYMD = "%Y-%m-%d";
	string timeStringTMDHMS = "%Y-%m-%d %X";
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
	ss << localMsg.constData() << '\n';

	switch (type) {
		case QtDebugMsg:
		case QtInfoMsg:
			*logging::fileStream << QString::fromStdString(ss.str());
			cout << ss.str();
			break;
		case QtWarningMsg:
		case QtCriticalMsg:
		case QtFatalMsg:
			cerr << ss.str();
	}
	if (type == QtFatalMsg) {
		abort();
	}
}

int main(int argc, char *argv[])
{
	// logging
	QDir dir("log");
	if (!dir.exists()) {
		dir.mkdir(".");
	}

	string fileName = logging::fileNamePrefix + getFormattedTime(logging::timeStringYMD) + logging::fileSuffix;

	QFile file(fileName.c_str());
	file.open(QIODevice::Append);
	logging::fileStream = new QTextStream(&file);

	QFileInfo fi(file);
	QTextStream(stdout) << "log file path: " << fi.absoluteFilePath() << '\n';

	const string timeStamp = getFormattedTime(logging::timeStringTMDHMS);

	*logging::fileStream << "\n<" << timeStamp.c_str() << ">\n";

	qInstallMessageHandler(myMessageOutput);
	// end of logging

	QApplication a(argc, argv);
	MainWindow w;
	w.show();
	auto result = a.exec();
	*logging::fileStream << "</" <<timeStamp.c_str() << ">\n";
	file.close();
	return result;
}
