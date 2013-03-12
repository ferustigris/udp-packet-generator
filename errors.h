#ifndef ERRORS_H
#define ERRORS_H
#include <QFile>
#include <QTextStream>
/*! класс журнала*/
class Log {
public:
	enum LogLevel{
		LOG_HLT = 1,//пипец
		LOG_SYS,//фатальные дшля системы
		LOG_APP,//фатальные для приложения
		LOG_ALARM,//фатальные опасности
		LOG_WARNING,//опасности
		LOG_INFO,//вывод информационных сообщений
		LOG_DEBUG//для дебакга
	};
	static void add (LogLevel level,  const QString &msg, LogLevel maxlevel = LOG_ALARM);
};

/*! класс предок исключений*/
class ECommonError {
public:
    ECommonError(const QString & _name);
    const QString& getName() {
	return name;
    }
private:
    QString name;
};
/*! класс исключения не найдена библиотека */
class ELibraryNotFound : public ECommonError {
public:
    ELibraryNotFound(const QString &name);
};

#endif // ERRORS_H
