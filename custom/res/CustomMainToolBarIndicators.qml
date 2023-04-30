/****************************************************************************
 *
 * (c) 2009-2020 QGROUNDCONTROL PROJECT <http://www.qgroundcontrol.org>
 *
 * QGroundControl is licensed according to the terms in the file
 * COPYING.md in the root of the source code directory.
 *
 ****************************************************************************/

import QtQuick 2.12
import QtQuick.Controls 2.4
import QtQuick.Layouts  1.11
import QtQuick.Dialogs  1.3

import QGroundControl               1.0
import QGroundControl.ScreenTools   1.0
import QGroundControl.Controls              1.0
import QGroundControl.Palette               1.0

//-------------------------------------------------------------------------
//-- Toolbar Indicators
Row {
    id:                 indicatorRow
    anchors.top:        parent.top
    anchors.bottom:     parent.bottom
    anchors.margins:    _toolIndicatorMargins
    spacing:            ScreenTools.defaultFontPixelWidth * 1.5

    property var  _activeVehicle:           QGroundControl.multiVehicleManager.activeVehicle
    property real _toolIndicatorMargins:    ScreenTools.defaultFontPixelHeight * 0.66

    Repeater {
        id:     appRepeater
        model:  QGroundControl.corePlugin.toolBarIndicators
        Loader {
            anchors.top:        parent.top
            anchors.bottom:     parent.bottom
            source:             modelData
            visible:            item.showIndicator
        }
    }

    Repeater {
        model: _activeVehicle ? _activeVehicle.toolIndicators : []
        Loader {
            anchors.top:        parent.top
            anchors.bottom:     parent.bottom
            source:             modelData
            visible:            item.showIndicator
        }
    }

    Repeater {
        model: _activeVehicle ? _activeVehicle.modeIndicators : []
        Loader {
            anchors.top:        parent.top
            anchors.bottom:     parent.bottom
            source:             modelData
            visible:            item.showIndicator
        }
    }

    property var _featureHandler: QGroundControl.corePlugin.featureHandler

    Button {
        id:                 featureAButton
        text:               qsTr("Feature A")
        anchors.top:        parent.top
        anchors.bottom:     parent.bottom
        onClicked:          mainWindow.showIndicatorPopup(_root, featureAInfo)
        visible:            _featureHandler.featureA

        background: Rectangle {
            id:             backRect
            color: "#fca5a5"
        }

        Component {
            id: featureAInfo

            Rectangle {
                width:                  roiCol.width   + ScreenTools.defaultFontPixelWidth  * 6
                height:                 roiCol.height  + ScreenTools.defaultFontPixelHeight * 2
                radius:                 ScreenTools.defaultFontPixelHeight * 0.5
                color:                  qgcPal.window

                Column {
                    id:                 roiCol
                    spacing:            ScreenTools.defaultFontPixelHeight * 0.5
                    width:              roiLabel.width
                    anchors.margins:    ScreenTools.defaultFontPixelHeight
                    anchors.centerIn:   parent

                    QGCLabel {
                        id:             roiLabel
                        text:           qsTr("Feature A Enabled!")
                        font.family:    ScreenTools.demiboldFontFamily
                        visible:        true
                        anchors.horizontalCenter: parent.horizontalCenter
                    }
                }
            }
        }
    }

    Button {
        id:                 featureBButton
        text:               qsTr("Feature B")
        anchors.top:        parent.top
        anchors.bottom:     parent.bottom
        onClicked:          mainWindow.showIndicatorPopup(_root, featureBInfo)
        visible:            _featureHandler.featureB

        background: Rectangle {
            id:             backBRect
            color:          "#93c5fd"
        }

        Component {
            id: featureBInfo

            Rectangle {
                width:                  roiBCol.width   + ScreenTools.defaultFontPixelWidth  * 6
                height:                 roiBCol.height  + ScreenTools.defaultFontPixelHeight * 2
                radius:                 ScreenTools.defaultFontPixelHeight * 0.5
                color:                  qgcPal.window

                Column {
                    id:                 roiBCol
                    spacing:            ScreenTools.defaultFontPixelHeight * 0.5
                    width:              roiBLabel.width
                    anchors.margins:    ScreenTools.defaultFontPixelHeight
                    anchors.centerIn:   parent

                    QGCLabel {
                        id:             roiBLabel
                        text:           qsTr("Feature B Enabled!")
                        font.family:    ScreenTools.demiboldFontFamily
                        visible:        true
                        anchors.horizontalCenter: parent.horizontalCenter
                    }
                }
            }
        }
    }
}
