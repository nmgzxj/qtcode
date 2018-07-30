#ifndef RULE_H
#define RULE_H
#include <QString>
#include <QList>


class Rule
{
public:
    Rule();
    QString getRuleName();
    QList<QString> getRules();
    void setRuleName(QString ruleName);
    void setRules(QList<QString> rules);
    void addRule(Rule rule);
private:
    QString ruleName;
    QList<QString> rules;

};

#endif // RULE_H

