//
//  AttachmentsDialog.h
//  interface/src/ui
//
//  Created by Andrzej Kapolka on 5/4/14.
//  Copyright 2014 High Fidelity, Inc.
//
//  Distributed under the Apache License, Version 2.0.
//  See the accompanying file LICENSE or http://www.apache.org/licenses/LICENSE-2.0.html
//

#ifndef hifi_AttachmentsDialog_h
#define hifi_AttachmentsDialog_h

#include <QDialog>

#include <AvatarData.h>

class QComboBox;
class QDoubleSpinner;
class QLineEdit;

/// Allows users to edit the avatar attachments.
class AttachmentsDialog : public QDialog {
    Q_OBJECT

public:
    
    AttachmentsDialog();

private slots:
    
    void addAttachment(const AttachmentData& data = AttachmentData());
};

/// A panel controlling a single attachment.
class AttachmentPanel : public QWidget {
    Q_OBJECT

public:
    
    AttachmentPanel(const AttachmentData& data = AttachmentData());

private slots:

    void chooseModelURL();
    void setModelURL(const QString& url);

private:
    
    QLineEdit* _modelURL;
    QComboBox* _jointName;
    QDoubleSpinBox* _translationX;
    QDoubleSpinBox* _translationY;
    QDoubleSpinBox* _translationZ;
    QDoubleSpinBox* _rotationX;
    QDoubleSpinBox* _rotationY;
    QDoubleSpinBox* _rotationZ;
    QDoubleSpinBox* _scale;
};

#endif // hifi_AttachmentsDialog_h
