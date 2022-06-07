import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Layouts 1.14
import QtQuick.Controls 2.5

ApplicationWindow {
    Popup {
        id: popup
        parent: Overlay.overlay
        x: Math.round((parent.width - width) / 2)
        y: Math.round((parent.height - height) / 2)
        width: 400
        height: 350
        modal: true
        ColumnLayout{
            Layout.fillWidth: true
            anchors.fill: parent
            TextField{
                id: popuppin
                placeholderText: "Введите ключ"
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                Layout.alignment: Qt.AlignCenter
                Layout.fillWidth: true
                Layout.margins: 20
                color: "black"
                font.pixelSize: 15
            }

            Label {
                id: indexField
                text: ""
                visible: false
            }

            Label {
                id: typeField
                text: ""
                visible: false
            }

            Button {
                id: popupClose
                Layout.alignment: Qt.AlignCenter
                contentItem: Text {
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    text: qsTr("  Вход  ")
                    font.pixelSize: 20

                }
                onClicked: {
                    makerDeff.copyToBufBarter(indexField.text, typeField.text, popuppin.text)
                    popup.close()
                    popuppin.clear()
                    indexField.text = ""
                    typeField.text = ""
                }
            }
        }
    }

    signal parserFunc(string pin)

    visible: true
    width: 600
    height: 800
    title: qsTr("Velikanov Pass Meneger")

    background: Rectangle {
        id:recttang
        color: "yellow"
    }

    ColumnLayout{
        Layout.fillWidth: true
        anchors.fill: parent
        Label {
            id: check
            Layout.alignment: Qt.AlignCenter
            font.pixelSize: 20
            text: "<b>УСПЕШНО<b>"
            color: "green"
            visible: false
        }
        Label {
            id: checkinf
            Layout.alignment: Qt.AlignCenter
            font.pixelSize: 20
            text: "<b>Неверный ключ<b>"
            color: "red"
            visible: false
        }
        Label {
            id: tosik
            visible: true
            font.pixelSize: 12
            Layout.alignment: Qt.AlignCenter
        }

        Label {
            id: labelauth
            Layout.alignment: Qt.AlignCenter
            font.pixelSize: 25
            text: "Введите ключ"
        }


        TextField{
            id: key
            visible: true
            cursorVisible: false
            //placeholderText: "Введите ключ"
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            Layout.alignment: Qt.AlignCenter
            Layout.fillWidth: true
            echoMode: "Password"
            Layout.margins: 20
            color: "grey"
            font.pixelSize: 20
        }

        Button {
            id: auth
            Layout.alignment: Qt.AlignCenter
            contentItem: Text {
                font.pixelSize: 20

                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                text: qsTr("  Вход  ")

            }

            onClicked: {
                if(key.text.length >= 3 && key.text.length <= 4)
                    makerDeff.openUrl();
                if(makerDeff.parserFunc(key.text, "") === false){
                    checkinf.visible = true

                }
                else {
                    checkinf.visible = false
                    key.visible = false
                    labelauth.visible = false
                    scrollview.visible = true
                    auth.visible = false
                    listView.visible = true
                }
            }
        }

    }


    ScrollView{
        id: scrollview
        anchors.fill: parent
        visible: false

        Layout.fillWidth: true
        Item {}

        ColumnLayout{
            anchors.fill: parent
            TextField{
                id: searchin
                Layout.fillWidth: true
                visible: true
                cursorVisible: false
                placeholderText: "Поиск"
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                Layout.margins: 20
                color: "black"
                font.pixelSize: 20
                onEditingFinished: {
                    makerDeff.parserFunc(key.text, searchin.text)
                    //                    listView.model.roleNames().forEach(el => console.log(el))
                }
            }

            ListView{
                id: listView
                Layout.margins: 20
                visible: false
                Layout.fillHeight: true
                Layout.fillWidth: true
                enabled: true
                model: sicretsmodal
                spacing: 10
                anchors.margins: 5
                //Layout.margins: 10

                delegate: Rectangle{
                    anchors.margins: 5
                    width: listView.width
                    height: 120
                    border.color: "red"
                    color: 'green'
                    radius: 5


                    GridLayout{
                        anchors.fill: parent
                        columns: 4

//                        Image{
//                            //                            source: "img/back.jpg"

//                            Layout.rowSpan: 3
//                            Layout.fillHeight: true
//                            Layout.preferredWidth: 100
//                            Layout.margins: 5
//                            fillMode: Image.PreserveAspectFit
//                            Layout.alignment: Qt.AlignCenter
//                        }
                        Label{
                            color: "black"
                            Layout.alignment: Qt.AlignVCenter
                            text: urlka
                            Layout.rowSpan: 3
                            Layout.margins: 20
                            Layout.preferredWidth: 120
                        }

                        Button {
                            id: givemelogin
                            Layout.alignment: Qt.AlignVCenter
                            Layout.rowSpan: 3
                            Layout.preferredWidth: 170
                            contentItem: Text {
                                horizontalAlignment: Text.AlignHCenter
                                verticalAlignment: Text.AlignVCenter
                                text: "Скопировать логин"
                                font.pixelSize: 15
                            }
                            onClicked: {
                                popup.open()
                                indexField.text = index
                                typeField.text = "login"
                            }
                        }


                        Button {
                            id: givemepassword
                            Layout.alignment: Qt.AlignVCenter
                            Layout.rowSpan: 3
                            Layout.preferredWidth: 170
                            contentItem: Text {
                                horizontalAlignment: Text.AlignHCenter
                                verticalAlignment: Text.AlignVCenter
                                text: "Скопировать пароль"
                                font.pixelSize: 15
                            }
                            onClicked: {
                                popup.open()
                                indexField.text = index
                                typeField.text = "password"
                            }
                        }
                    }
                }
            }
        }
    }
}
