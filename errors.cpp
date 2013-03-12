#include <QDir>
#include "errors.h"

/*!\func LOG
 * ���������� ��������� � ������
 * \param
 * - level - ��������� ���������
 * - msg - ���������
 * - _maxlevel - ������� ��������������
 * \return ���
 */
void Log::add (LogLevel level, const QString& msg, LogLevel _maxlevel)
{
	QFile file("../var/log/main.log");
	QTextStream text;
	static quint8 maxlevel;
	if(maxlevel!= _maxlevel)maxlevel = _maxlevel;
	QDir dir;
	dir.mkpath("../var/log/");
	file.open(QIODevice::ReadWrite);
	text.setDevice(&file);
	text.seek(file.size());
	if (level <= maxlevel)
		text<<msg<<"\n";
}

/*!\func LOG
 * ������ �����
 * \param
 * - _name - ��� ������, ��������
 * \return ���
 */
ECommonError::ECommonError(const QString & _name) {
    name = _name;
    //LOG(LOG_DEBUG, name);
}
/*!\func LOG
 * ������ ���������� �� �������, �� ��������� ��� ����������
 * \param
 * - _name - ��� ������, ��������
 * \return ���
 */
ELibraryNotFound::ELibraryNotFound(const QString &name):ECommonError(name){
	Log log;
	log.add(Log::LOG_ALARM, name);
}
