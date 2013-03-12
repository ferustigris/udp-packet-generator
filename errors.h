#ifndef ERRORS_H
#define ERRORS_H
#include <QFile>
#include <QTextStream>
/*! ����� �������*/
class Log {
public:
	enum LogLevel{
		LOG_HLT = 1,//�����
		LOG_SYS,//��������� ���� �������
		LOG_APP,//��������� ��� ����������
		LOG_ALARM,//��������� ���������
		LOG_WARNING,//���������
		LOG_INFO,//����� �������������� ���������
		LOG_DEBUG//��� �������
	};
	static void add (LogLevel level,  const QString &msg, LogLevel maxlevel = LOG_ALARM);
};

/*! ����� ������ ����������*/
class ECommonError {
public:
    ECommonError(const QString & _name);
    const QString& getName() {
	return name;
    }
private:
    QString name;
};
/*! ����� ���������� �� ������� ���������� */
class ELibraryNotFound : public ECommonError {
public:
    ELibraryNotFound(const QString &name);
};

#endif // ERRORS_H
