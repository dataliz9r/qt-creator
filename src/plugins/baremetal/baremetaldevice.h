/****************************************************************************
**
** Copyright (C) 2016 Tim Sander <tim@krieglstein.org>
** Copyright (C) 2016 Denis Shienkov <denis.shienkov@gmail.com>
** Contact: https://www.qt.io/licensing/
**
** This file is part of Qt Creator.
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 as published by the Free Software
** Foundation with exceptions as appearing in the file LICENSE.GPL3-EXCEPT
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
****************************************************************************/

#pragma once

#include <projectexplorer/devicesupport/idevice.h>
#include <projectexplorer/devicesupport/idevicefactory.h>

namespace BareMetal {
namespace Internal {

class GdbServerProvider;

class BareMetalDevice : public ProjectExplorer::IDevice
{
public:
    using Ptr = QSharedPointer<BareMetalDevice>;
    using ConstPtr = QSharedPointer<const BareMetalDevice>;

    static Ptr create() { return Ptr(new BareMetalDevice); }
    ~BareMetalDevice() override;

    QString displayType() const override;
    ProjectExplorer::IDeviceWidget *createWidget() override;
    Utils::OsType osType() const override;
    ProjectExplorer::IDevice::Ptr clone() const override;

    ProjectExplorer::DeviceProcessSignalOperation::Ptr signalOperation() const override;

    bool canCreateProcess() const override { return true; }
    ProjectExplorer::DeviceProcess *createProcess(QObject *parent) const override;

    QString gdbServerProviderId() const;
    void setGdbServerProviderId(const QString &id);
    void unregisterProvider(GdbServerProvider *provider);
    void providerUpdated(GdbServerProvider *provider);

    void fromMap(const QVariantMap &map) override;
    QVariantMap toMap() const override;

private:
    BareMetalDevice() = default;
    BareMetalDevice(const BareMetalDevice &other);

    void setChannelByServerProvider(GdbServerProvider *provider);
    BareMetalDevice &operator=(const BareMetalDevice &);
    QString m_gdbServerProviderId;
};

class BareMetalDeviceFactory : public ProjectExplorer::IDeviceFactory
{
    Q_OBJECT

public:
   BareMetalDeviceFactory();

   ProjectExplorer::IDevice::Ptr create() const override;
};

} //namespace Internal
} //namespace BareMetal
