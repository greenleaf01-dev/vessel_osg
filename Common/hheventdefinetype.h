//在提交头文件时最好把各个参数的说明以注释形式给出
//使用了多少个type要在这里使用define宏
//例如：#define XXX_H_COUNT 100
#include "../GeneralTool/GeneralToolEvent_Type.h"
#define GENERALTOOLEVENT_COUNT 4
#include "../Foundation/data/dataevent_type.h"
#define FOUNDATIONDATAEVENT_COUNT 1

const QEvent::Type	HH_EVENT_SAVE_FILE_BEGIN = (QEvent::Type)(QEvent::User + 6);

const QEvent::Type	HH_EVENT_SAVE_FILE_END= (QEvent::Type)(QEvent::User + 7);