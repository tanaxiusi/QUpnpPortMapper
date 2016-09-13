
#include <QCoreApplication>
#include <QNetworkInterface>
#include "QUpnpPortMapper.h"
#include <iostream>

int main(int argc, char *argv[])
{
	QCoreApplication app(argc, argv);

	// list all NetworkInterface and choose one, or you can get your local address by calling a connected QTcpSocket with localAddress()
	QUpnpPortMapper mapper;
	QList<QNetworkInterface> allCards = QNetworkInterface::allInterfaces();
	for (int i = 0; i < allCards.size(); ++i)
	{
		QString line = QString("[%1] %2").arg(i + 1).arg(allCards[i].humanReadableName());
		qDebug() << line;
	}

	std::cout << "Choose : ";
	int index = 0;
	std::cin >> index;
	if (index < 1 || index > allCards.size())
		return 0;

	// firstly, open
	mapper.open(allCards.at(index - 1));
	qDebug() << QString("Internal address : %1").arg(mapper.localAddress().toString());

	// then discover
	if (!mapper.discover(5000, true))
	{
		qDebug() << "No upnp support";
		return 0;
	}

	// however, queryExternalAddress is not necessary
	qDebug() << "External address " << mapper.queryExternalAddress(true).toString();

	qDebug() << "Input internal & external port:";
	int internalPort, externalPort;
	std::cin >> internalPort >> externalPort;

	// you can use TCP or UDP, the description must be REGULAR in order to not corrupt the posted XML
	bool ok = mapper.addPortMapping(QAbstractSocket::TcpSocket, mapper.localAddress(), internalPort, externalPort, "test", true);
	if (ok)
		qDebug() << "Mapping ok";
	else
	{
		qDebug() << "Mapping failed";
		return 0;
	}

	return app.exec();
}
