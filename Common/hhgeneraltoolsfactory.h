#pragma once

#include "generaltool_global.h"
#include "../Common/hhgeneraltoolsfactory.h"

#include <QObject>

class IHHCurtainItem;
class IHHSpotLightTool;
class IHHMagnifiertTool;

//工具使用对象
enum HHGeneralToolsMode
{
	//鸿合白板
	HHWhiteBoard = 0x100,
	//鸿合大小屏互动
	HHSizeScreenInteraction,
	//PPT助手
	HHPPTHelper,
};

class GENERALTOOL_EXPORT HHGeneralToolsFactory : public QObject
{
    Q_OBJECT
public:

    static QWidget* getMathItem(const QString &itemID, QWidget *parent);
    static  IHHCurtainItem* getCurtainItem();    
	
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// <summary>	创建聚光灯. </summary>
    ///
    /// <remarks>	GanSonglin, 2018/4/3. </remarks>
    ///
    /// <param name="parent">		  	[in] (Optional) 父窗口，可以缺省. </param>
    /// <param name="isNotWhiteBoard">	(Optional) 模式 . </param>
    ///
    /// <returns>	成功返回聚光灯，失败返回nullptr. </returns>
    ///
    /// <example>	. </example>
    ///
    /// <inheritdoc/>
    ////////////////////////////////////////////////////////////////////////////////////////////////////

    static IHHSpotLightTool *createSpotLightTool(QWidget *parent = nullptr, HHGeneralToolsMode GeneralToolsMode = HHWhiteBoard);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	创建放大镜. </summary>
	/// <remarks>	GanSonglin, 2018/4/3. </remarks>
	/// <param name="parent">		  	[in] (Optional) 父窗口，可以缺省. </param>
	/// <param name="isNotWhiteBoard">	(Optional) 模式  . </param>
	/// <returns>	成功返回放大镜，失败返回nullptr. </returns>
	/// <example>	. </example>
	/// <inheritdoc/>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	static IHHMagnifiertTool *createMagnifiertoolTool(QWidget *parent = nullptr, HHGeneralToolsMode GeneralToolsMode = HHWhiteBoard);
};
