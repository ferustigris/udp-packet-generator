#include <QDir>
#include "errors.h"

/*!\func LOG
 * записывает сообщение в журнал
 * \param
 * - level - приоретет сообщения
 * - msg - сообщение
 * - _maxlevel - уровень журналирования
 * \return нет
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
 * ошибка общая
 * \param
 * - _name - имя ошибки, описание
 * \return нет
 */
ECommonError::ECommonError(const QString & _name) {
    name = _name;
    //LOG(LOG_DEBUG, name);
}
/*!\func LOG
 * ошибка библиотека не найдена, не загружена или повреждена
 * \param
 * - _name - имя ошибки, описание
 * \return нет
 */
ELibraryNotFound::ELibraryNotFound(const QString &name):ECommonError(name){
	Log log;
	log.add(Log::LOG_ALARM, name);
}
