/**
 * $Id: lookup.js,v 1.10 2011/04/21 19:04:27 cyl2478 Exp $
 */

/**
 * insert a row into a <table> element
 * @param tableName The id to the table String
 * @param vars The variables in Javascript Array format ie Array("ABC","123","DEF","456");
 * @param includeRemoveCol flag to automatically generate a '[Remove]' cell
 * @param rowId provide a rowId, or it will be randomly generated
 * @param insertFirstRow flag to tell if I want to insert as first row or false to last row (always assume there is a header row)
 */
function insertRow(tableName, vars, includeRemoveCol, rowId, insertFirstRow) {
	var table = $(tableName);
	var lastRow = table.insertRow(insertFirstRow ? 0 : table.rows.length);
	var id = rowId == null ? Math.random() : rowId;
	lastRow.id = id;
	var headerRow = table.rows[0];
	
	if (vars == null || vars.length == 0) {
		// Insert a NONE row
		var cell = lastRow.insertCell(0);
		cell.setAttribute("colspan", headerRow.children.length);
		cell.setAttribute("class", "centeralign");
		var textNode = document.createTextNode("NONE");
		cell.appendChild(textNode);
	} else {
		for (var i = 0; i < vars.length; i++) {
			var cell = lastRow.insertCell(i);
			if (vars[i] instanceof Object) {
				if (vars[i] instanceof Array) {
					for (var j = 0; j < vars[i].length; j++) {
						if (vars[i][j] instanceof Array) {
							handleArray(vars[i][j], cell);
						} else if (vars[i][j] instanceof MyObject) {
							cell.appendChild(getElementFromMyObject(vars[i][j]));
						} else {
							cell.appendChild(document.createTextNode(vars[i][j]));
						}
					}
				} else if (vars[i] instanceof MyObject) {
					cell.appendChild(getElementFromMyObject(vars[i]));
				}
			} else {
				var textNode = document.createTextNode(unescape(vars[i]));
				cell.appendChild(textNode);
			}
		}
		
		if (includeRemoveCol) {
			var cell = lastRow.insertCell(vars.length);
			var button = document.createElement("a");
			button.style.cursor = "pointer";
			button.onclick = function() { removeRow(id); };
			button.innerHTML = "[Remove]";
			cell.appendChild(button);
		}
	}	
}

function handleArray(myObject, cell) {
	for (var i = 0; i < myObject.length; i++) {
		if (myObject[i] instanceof Array) {
			handleArray(myObject[i], cell);
		} else if (myObject[i] instanceof MyObject) {
			cell.appendChild(getElementFromMyObject(myObject[i]));
		} else {
			cell.appendChild(document.createTextNode(myObject[i]));
		}
	}
}


function getElementFromMyObject(myObject) {
	var element = document.createElement(myObject.elementType);
	for (var k = 0; k < myObject.attributes.length; k++) {
		element.setAttribute(myObject.attributes[k].name, myObject.attributes[k].value);
	}
	if (myObject.content != null) {
		if (myObject.content instanceof Array) {
			for (var i = 0; i < myObject.content.length; i++) {
				if (myObject.content[i] instanceof MyObject) {
					element.appendChild(getElementFromMyObject(myObject.content[i]));
				} else {
					element.innerHTML = myObject.content;
				}
			}
		} else if (myObject.content instanceof MyObject) {
			element.appendChild(getElementFromMyObject(myObject.content));
		} else {
			element.innerHTML = myObject.content;
		}
	}
	return element;
}


/**
 * Remove a row
 * @param rowId Row to be remove
 */
var numberOfConfirm = 0;
function removeRow(rowId) {
	var table = $(rowId).up('table');
	if (numberOfConfirm > 0 || confirm("Remove this row?")) {
		$(rowId).remove();
		numberOfConfirm++;
	}
	
	if (table.rows.length == 1) {
		var div = table.up('div', 1);
		Effect.BlindUp (div.id, {duration : 1});
	}
}

/**
 * Remove all rows from the provided table
 * @param tableName
 */
function remove_all_rows(tableName) {
	var table = $(tableName);
	for (var i = table.rows.length - 2; i > 0; i--) {
		table.rows[i].remove();
	}
}

/**
 * MyObject holder
 * @param elementType (input, a, etc...)
 * @param attributes Array of attributes such as class, type, value, id, etc...
 * @return a custom object
 */
function MyObject(elementType, attributes, content) {
	this.elementType = elementType;
	this.attributes = attributes;
	this.content = content;
}

/**
 * Attribute holder
 * @param name attribute name
 * @param value attribute value
 * @return attribute
 */
function MyAttribute(name, value) {
	this.name = name;
	this.value = value;
}