//#include <QApplication>

// 是否使用配置文件
#define UseConfigFile true

#include <QDir>
#include "iostream"
#include "stdio.h"
#include "log4cplus/logger.h"
#include "log4cplus/consoleappender.h"
#include "log4cplus/layout.h"
#include "log4cplus/loggingmacros.h"
#include "log4cplus/configurator.h"

using namespace log4cplus;
using namespace log4cplus::helpers;

int main(int argc, char *argv[])
{
    QDir *m_dir = new QDir();

    std::string m_configDir = m_dir->dirName().toStdString() +"/tracelog.properties";

    std::cout << m_configDir <<std::endl;

    // setup4 : 实例化一个日志输出对象（后面的宏要用到）
    Logger _logger = Logger::getInstance("test");

    if(UseConfigFile)
    {
        // 加载 log4cplus 配置
        log4cplus::PropertyConfigurator::doConfigure(m_configDir);
    }
    else
    {
        /* step 1: 实例化一个输出介质对象 */

        SharedObjectPtr<Appender> _append (new ConsoleAppender());

        _append->setName("append for  test");


        /* step 2: 实例化一个输出格式对象 */

        std::string pattern = "%d{%m/%d/%y  %H:%M:%S}  - %m [%l]%n";

        std::auto_ptr<Layout> _layout(new PatternLayout(pattern));


        /* step 3: 将 layout对象 绑定到 append 对象 */

        _append->setLayout( _layout );


        /* step 4:  Instantiate a logger object */

        //Logger _logger = Logger::getInstance("test");


        /* step 5: 将 append 绑定到 logger 日志输出对象  */

        _logger.addAppender(_append);


        /* step 6: 设置日志登记  */

        _logger.setLogLevel(ALL_LOG_LEVEL);
    }


    /* log activity  十万次*/
    for(int i=0;i<100000;i++)
    {
        LOG4CPLUS_DEBUG(_logger, "This is the  Debug log message...");

        LOG4CPLUS_WARN(_logger, "This is the   Warn log message...");

        LOG4CPLUS_ERROR(_logger,"This is the   ERROR log message...");

        LOG4CPLUS_FATAL(_logger,"This is the   Fatal log message...");
    }
}


