/**
 * \author Andreas Misje
 * \date 2014
 * \copyright MIT
 */

import QtQuick 2.0
import QDrive 1.0
import QtQuick.Controls 1.1

Rectangle {
	width: 900
	height: 200
	color: '#161616'

	PartitionListModel {
		id: partitionModel
		onDBusError: console.log('DBUS ERROR: ' + errorMessage)
		drivePropertyFilter: ({ 
			usb: true,
			removable: true,
			mediaAvailable: true
		})
		/* Not really necessary, because setting drivePropertyFilter will call
		 * enumerate(): */
		Component.onCompleted: enumerate()
	}

	TableView {
		anchors.fill: parent
		model: partitionModel

		TableViewColumn {
			role: 'DriveVendor'
			title: qsTr('Vendor')
			width: 100
			delegate: itemDelegate
		}
		TableViewColumn {
			role: 'DriveModel'
			title: qsTr('Model')
			width: 140
			delegate: itemDelegate
		}
		TableViewColumn {
			role: 'PartitionLabel'
			title: qsTr('Label')
			width: 200
			delegate: itemDelegate
		}
		TableViewColumn {
			role: 'PartitionSize'
			title: qsTr('Partition size')
			width: 100
			delegate: Item {
				Text {
					anchors.verticalCenter: parent.verticalCenter
					text: dataSizeString(styleData.value)
				}
			}
		}
		TableViewColumn {
			role: 'PartitionMounted'
			title: qsTr('Mounted')
			width: 70
			delegate: Item {
				Text {
					anchors.verticalCenter: parent.verticalCenter
					text: styleData.value
				}
			}
		}

		Component {
			id: itemDelegate
			Item {
				Text {
					anchors.verticalCenter: parent.verticalCenter
					text: styleData.value ? styleData.value : ''
				}
			}
		}
	}

	function dataSizeString(dataSize) {
		if (dataSize) {
			if (dataSize < 1048576) {
				return qsTr('%1 kB').arg((dataSize/1024).toFixed(0))
			}
			else if (dataSize < 1073741824) {
				return qsTr('%1 MB').arg((dataSize/1048576).toFixed(0))
			}
			else {
				return qsTr('%1 GB').arg((dataSize/1073741824).toFixed(1))
			}
		}
		else return '–'
	}
}
