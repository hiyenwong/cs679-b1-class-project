function doubleClickMove(fromSelectId, toSelectId, limits) {
	var from = $(fromSelectId);
	var to = $(toSelectId);
	var selected = getSelectedCountOnMultiSelect(toSelectId);
	
	if (from == null) {
		alert("Error, I can not retrieve options to an undefined multi-select form");
		return;
	}
	
	if (to == null) {
		alert("Error, I can not move options to an undefined multi-select form");
		return;
	}
	
	for (var i = (from.options.length - 1); i >= 0; i--) {
		if (limits > 0 && selected > limits) {
			alert('You have reach the preset upper limit (' + limits + ') number of options.');
			return;
		}
		
		if (from.options[i].selected) {
			selected++;
		    addOptionToSelect(toSelectId, from.options[i].value, from.options[i].text);
		    from.remove(i);
		    break;
		}
	}
}

function moveSelectOption(fromSelectId, toSelectId, limits) {
	var from = $(fromSelectId);
	var to = $(toSelectId);
	var selected = getSelectedCountOnMultiSelect(toSelectId);
	
	if (from == null) {
		alert("Error, I can not retrieve options to an undefined multi-select form");
		return;
	}
	
	if (to == null) {
		alert("Error, I can not move options to an undefined multi-select form");
		return;
	}

	for (var i = (from.options.length - 1); i >= 0; i--) {
		if (limits > 0 && selected > limits) {
			alert('You have reach the preset upper limit (' + limits + ') number of options.');
			return;
		}
		
		if (from.options[i].selected) {
			selected++;
		    addOptionToSelect(toSelectId, from.options[i].value, from.options[i].text);
		    from.remove(i);
		}
	}
}

function moveAllOptions(fromSelectId, toSelectId, limits) {
	var from = $(fromSelectId);
	var to = $(toSelectId);
	var selected = getSelectedCountOnMultiSelect(toSelectId);
	
	if (from == null) {
		alert("Error, I can not retrieve options to an undefined multi-select form");
		return;
	}
	
	if (to == null) {
		alert("Error, I can not move options to an undefined multi-select form");
		return;
	}

	for (var i = (from.options.length - 1); i >= 0; i--) {
		if (limits > 0 && selected > limits) {
			alert('You have reach the preset upper limit (' + limits + ') number of options.');
			return;
		}
		selected++;
	    addOptionToSelect(toSelectId, from.options[i].value, from.options[i].text);
	    from.remove(i);
	}
	
	if (to.length < 500) {
		sortSelect(to);
	}
}

function removeAllSelect(selectId) {
	for (var i = $(selectId).options.length - 1; i >= 0; i--) {
		$(selectId).remove(i);
	}
}

function removeOptionFromSelect(selectElement) {
	removeOptionFromSelectByIndex(selectElement, selectElement.selectedIndex);
}

function removeOptionFromSelectByInnerHTML(element, text) {
	for (var i = element.length - 1; i >= 0; i--) {
		if (element.options[i].innerHTML == text) {
			removeOptionFromSelectByIndex(element, i);
		}
	}
}

function removeOptionFromSelectByValue(element, value) {
	for (var i = element.length - 1; i >= 0; i--) {
		if (element.options[i].value == value) {
			removeOptionFromSelectByIndex(element, i);
		}
	}
}

function removeOptionFromSelectByIndex(element, index) {
	element.remove(index);
}

function addOptionToSelect(selectId, value, displayText) {
	var optn = document.createElement("OPTION");
	optn.text = displayText;
	optn.value = value;
	
	var inserted = false;
	var i = 0;
	var element = $(selectId);
	for (; i < element.options.length; i++) {
		if (element.options[i].text > displayText) {
			inserted = true;
			addElement(element, i, optn);
			break;
		}
	}
	
	if (!inserted) {
		// Inserting to the end because compare did not find a location;
		// Could be the first element if list is empty or the last element
		addElement(element, i, optn);
	}
}

function addElement(element, index, option) {
	try {
		// standards compliant; doesn't work in IE
		element.add(option, element.options[index]);
	} catch (ex) {
		// IE only
		element.add(option, index);
	}
}



function sortSelect(selectId) {
	var list = new Array();

	var s = $(selectId);
	// Gather all the options
	for (var i = (s.options.length - 1); i >= 0; i--) {
		var optn = new Object();
		optn.text = s.options[i].text;
		optn.value = s.options[i].value;
		list.push(optn);
	}

	list.sort(sortSelectFunction);
	removeAllSelect(selectId);
	for (var i = 0; i < list.length; i++) {
		addOptionToSelect(selectId, list[i].value, list[i].text);
	}
}

function sortSelectFunction(a, b) {
	if (a.value == b.value) {
		return 0;
	} else {
		return a.text < b.text ? -1 : 1;
	}
}

function getValueFromMultiSelect(selectId) {
	return getValueFromMultiSelectWithOption(selectId, false);
}

function getSelectedValueFromMultiSelect(selectId) {
	return getValueFromMultiSelectWithOption(selectId, true);
}

function getValueFromMultiSelectWithOption(selectId, selected) {
	var element = $(selectId);
	var selectedValues = new Array();
	for (var i = 0; i < element.options.length; i++) {
		if (selected) {
			if (element.options[i].selected) {
				selectedValues.push(element.options[i].value);
			}
		} else {
			selectedValues.push(element.options[i].value);
		}
	}
	return selectedValues;
}

function getSelectedValue(selectId) {
	return $(selectId).options[getSelectedIndex(selectId)].innerHTML.trim();
}

function getSelectedIndex(selectId) {
	var element = $(selectId);
	for (var i = 0; i < element.options.length; i++) {
		if (element.options[i].selected) {
			return i;
		}
	}
}

function getSelectedCountOnMultiSelect(selectId) {
	var counter = 0;
	var element = $(selectId);
	for (var i = 0; i < element.options.length; i++) {
		counter++;
	}
	return counter;
}