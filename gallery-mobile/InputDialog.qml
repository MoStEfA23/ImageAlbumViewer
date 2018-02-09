import QtQuick 2.9
import QtQuick.Controls 2.3
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.3
import "."

Dialog{

    property string label: "New item"
    property string hint: ""
    property alias editText: editTextItem
    standardButtons: Dialog.Ok | Dialog.Cancel

    onVisibleChanged: {
        editTextItem.focus = true
        editTextItem.selectAll()
    }

    onButtonClicked: {

    }

    Rectangle{
        implicitWidth: parent.width
        implicitHeight: 100


        ColumnLayout{
            Text {
                id: labelItem
                text: label
                color: Style.text
            }

            TextInput{
                id: editTextItem
                inputMethodHints: Qt.ImhPreferUppercase
                text: hint
                color: Style.text
            }
        }
    }
}
