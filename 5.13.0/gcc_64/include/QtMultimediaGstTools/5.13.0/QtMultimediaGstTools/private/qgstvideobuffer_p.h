/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 3 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL3 included in the
** packaging of this file. Please review the following information to
** ensure the GNU Lesser General Public License version 3 requirements
** will be met: https://www.gnu.org/licenses/lgpl-3.0.html.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 2.0 or (at your option) the GNU General
** Public license version 3 or any later version approved by the KDE Free
** Qt Foundation. The licenses are as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL2 and LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-2.0.html and
** https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef QGSTVIDEOBUFFER_P_H
#define QGSTVIDEOBUFFER_P_H

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API. It exists purely as an
// implementation detail. This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.
//

#include <private/qgsttools_global_p.h>
#include <qabstractvideobuffer.h>
#include <QtCore/qvariant.h>

#include <gst/gst.h>
#include <gst/video/video.h>

QT_BEGIN_NAMESPACE

#if GST_CHECK_VERSION(1,0,0)
class Q_GSTTOOLS_EXPORT QGstVideoBuffer : public QAbstractPlanarVideoBuffer
{
public:
    QGstVideoBuffer(GstBuffer *buffer, const GstVideoInfo &info);
    QGstVideoBuffer(GstBuffer *buffer, const GstVideoInfo &info,
                    HandleType handleType, const QVariant &handle);
#else
class Q_GSTTOOLS_EXPORT QGstVideoBuffer : public QAbstractVideoBuffer
{
public:
    QGstVideoBuffer(GstBuffer *buffer, int bytesPerLine);
    QGstVideoBuffer(GstBuffer *buffer, int bytesPerLine,
                    HandleType handleType, const QVariant &handle);
#endif

    ~QGstVideoBuffer();

    GstBuffer *buffer() const { return m_buffer; }
    MapMode mapMode() const override;

#if GST_CHECK_VERSION(1,0,0)
    int map(MapMode mode, int *numBytes, int bytesPerLine[4], uchar *data[4]) override;
#else
    uchar *map(MapMode mode, int *numBytes, int *bytesPerLine) override;
#endif

    void unmap() override;

    QVariant handle() const override { return m_handle; }
private:
#if GST_CHECK_VERSION(1,0,0)
    GstVideoInfo m_videoInfo;
    GstVideoFrame m_frame;
#else
    int m_bytesPerLine;
#endif
    GstBuffer *m_buffer;
    MapMode m_mode;
    QVariant m_handle;
};

QT_END_NAMESPACE

#endif
