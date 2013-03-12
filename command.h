#ifndef COMMAND_H
#define COMMAND_H
#include <QByteArray>
//! class, who representative command
class Command {
public:
    Command( const bool rw, const bool waitAnswer, const bool increment, const qint8 answerBody);
    ~Command();
public:
    qint8 getCommand() const;
    bool getRw() const;
    bool getAnswer() const;
    bool getIncrement() const;
    bool getWaitAnswer() const;
    void setCommand(const qint8 flag);
    void setRw(const bool flag);
    void setAnswer(const bool flag);
    void setIncrement(const bool flag);
    void setWaitAnswer(const bool flag);
private:
    bool rw;
    bool increment;
    bool waitAnswer;
    qint8 answerBody;
};

#endif // COMMAND_H
