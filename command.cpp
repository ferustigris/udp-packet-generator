#include "command.h"

/*!\func
 * constructor
 * \param no
 * \return no
 */
Command::Command(const bool rw, const bool waitAnswer, const bool increment, const qint8 answerBody)
{
    this->rw = rw;
    this->increment = increment;
    this->waitAnswer = waitAnswer;
    this->answerBody = answerBody;
}/*!\func
 * destructor
 * \param no
 * \return no
 */
Command::~Command()
{
}
/*!\func
 * return command
 * \param no
 * \return no
 */
qint8 Command::getCommand() const
{
    qint8 result = 0;
    if(rw)result |= 0x80;
    if(waitAnswer)result |= 0x40;
    if(increment)result |= 0x20;
    result |= answerBody;
    return result;
}
/*!\func
 * return read/write flag
 * \param no
 * \return no
 */
bool Command::getRw() const
{
	return rw;
}
/*!\func
 * return answer flag
 * \param no
 * \return no
 */
bool Command::getWaitAnswer() const
{
	return waitAnswer;
}
/*!\func
 * return increment flag
 * \param no
 * \return no
 */
bool Command::getIncrement() const
{
	return increment;
}
/*!\func
 * set rw flag
 * \param no
 * \return no
 */
void Command::setRw(const bool flag)
{
	rw = flag;
}
/*!\func
 * return increment flag
 * \param no
 * \return no
 */
void Command::setAnswer(const bool flag)
{
	Q_UNUSED (flag);
	//answer = flag;
}
/*!\func
 * return increment flag
 * \param no
 * \return no
 */
void Command::setIncrement(const bool flag)
{
	increment = flag;
}
/*!\func
 * return increment flag
 * \param no
 * \return no
 */
void Command::setWaitAnswer(const bool flag)
{
	waitAnswer = flag;
}
/*!\func
 * return increment flag
 * \param no
 * \return no
 */
void Command::setCommand(const qint8 flag)
{
	rw = flag & 0x80;
	waitAnswer = flag & 0x40;
	increment = flag & 0x20;
	answerBody = flag & 0x0F;
}