#pragma once

// ΩÁ√ÊIceøÿ÷∆
class IHHIceWhiteBoardManger {
public:
	~IHHIceWhiteBoardManger() {}

	virtual QObject *getObject() = 0;

	//virtual void notifyPlayed(const QVariantMap &info) = 0;
	//virtual void notifyStoped(const QVariantMap &info) = 0;

	//virtual void notifyShowNexted(const QVariantMap &info) = 0;
	//virtual void notifyShowForwarded(const QVariantMap &info) = 0;
	//virtual void notifyShowSlided(const QVariantMap &info) = 0;
};

Q_DECLARE_INTERFACE(IHHIceWhiteBoardManger, "org.qt-project.Qt.IHHIceWhiteBoardManger");