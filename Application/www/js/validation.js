/**
 * $Id: validation.js,v 1.4 2012/01/13 17:31:41 cyl2478 Exp $
 */
function validateFields(fields) {
	var error = "Missing required parameter(s):";
	var hasMultiple = 0;
	var hasError = false;

	for (var i = 0; i < fields.length; i++) {
		// This is a backward compatibility fix for incase something defines it ie: validateFields(new Array("ABC","DEF"));
		if (typeof fields[i] === "string") {
			fields[i] = new Field(fields[i]);
		}
		
		// Field does not exist, but why fail its? its a programmer's error, not user. Let controller handles it
		//if ($F(fields[i].fieldId) == null) {
		//	continue;
		//}
		
		if (fields[i] instanceof Field) {
			if ($F(fields[i].fieldId).strip() == '') {
				$(fields[i].fieldId).addClassName('errorinput');
				error += " "+fields[i].fieldId+",";
				hasError = true;
				hasMultiple++;
			} else {
				$(fields[i].fieldId).removeClassName('errorinput');
			}
		} else if (fields[i] instanceof SelectField) {
			if (!selectValidate(fields[i].fieldId, fields[i].numberNeeded, fields[i].maxOrMin, fields[i].selected)) {
				error += " "+fields[i].fieldId+",";
				hasError = true;
				hasMultiple++;
			}
		} else if (fields[i] instanceof ArrayField) {
			if (!fieldArrayValidate(fields[i].fieldId, fields[i].numberNeeded, fields[i].maxOrMinOrEqual)) {
				error += " "+fields[i].fieldId+",";
				hasError = true;
				hasMultiple++;
			}
		}
	}

	if (hasError) {
		alert("Missing highlighted field" + (hasMultiple > 1 ? "s" : ""));
		return false;
	} else {
		return true;
	}
}

/**
 * Validator for select box
 * @param selectId element id
 * @param numberNeeded number to restrict to
 * @param maxOrMin Max means not exceeding, Min means no less than
 * @param selected True: Select box must be selected # of options; False: Select box must contain # of options
 * @return Has the element pass the validation
 */
function selectValidate(selectId, numberNeeded, maxOrMin, selected) {
	var selectedCount = 0;
	var element = $(selectId);
	for (var i = (element.options.length - 1); i >= 0; i--) {
		if (selected) {
			if (element.options[i].selected && element.options[i].value.strip() != "") {
				selectedCount++;
			}
		} else {
			selectedCount++;
		}
	}
	
	if (maxOrMin == 'max') {
		if (selectedCount > numberNeeded) {
			$(selectId).addClassName('errorinput').removeClassName('MB_focusable');
			return false;
		} else {
			$(selectId).removeClassName('errorinput');
			return true;
		}
	} else if (maxOrMin == 'min') {
		if (selectedCount < numberNeeded) {
			$(selectId).addClassName('errorinput').removeClassName('MB_focusable');
			return false;
		} else {
			$(selectId).removeClassName('errorinput');
			return true;
		}
	} else {
		if (selectedCount < 1) {
			$(selectId).addClassName('errorinput').removeClassName('MB_focusable');
			return false;
		} else {
			$(selectId).removeClassName('errorinput');
			return true;
		}
	}
}

/**
 * Validation for an array of elements, such as name="something[]" for checkboxes, hidden input, etc..
 * @param fieldId element name
 * @param numberNeeded number to restrict to
 * @param maxOrMinOrEqual Max means not exceeding, Min means no less than, everything else is Equal to numberNeeded
 * @return Has the elements pass the validation
 */
function fieldArrayValidate (fieldId, numberNeeded, maxOrMinOrEqual) {
	var elements = document.getElementsByName(fieldId);
	var valid = false;
	var count = 0;
	
	for (var i = 0; i < elements.length; i++) {
		if (elements[i].value != '') {
			count++;
		}
	}
	
	if (maxOrMinOrEqual == 'max') {
		valid = (elements.length <= numberNeeded);
	} else if (maxOrMinOrEqual == 'min') {
		valid = (count >= numberNeeded);
	} else {
		valid = (count == numberNeeded);
	}
	
	if (valid) {
		for (var i = 0; i < elements.length; i++) {
			elements[i].removeClassName('errorinput');
		}
	} else {
		for (var i = 0; i < elements.length; i++) {
			elements[i].addClassName('errorinput').removeClassName('MB_focusable');
		}
	}
	
	return valid;
}


/**
 * Normal Field Validation Object
 * @param fieldId element id
 */
function Field(fieldId) {
	this.fieldId = fieldId;
}

/**
 * SelectField Validation Object
 * @param fieldId element id
 * @param numberNeeded number to restrict to
 * @param maxOrMin Max means not exceeding, Min means no less than
 * @param selected True: Select box must be selected # of options; False: Select box must contain # of options
 */
function SelectField(fieldId, numberNeeded, maxOrMin, selected) {
	this.fieldId = fieldId;
	this.numberNeeded = numberNeeded;
	this.maxOrMin = maxOrMin;
	this.selected = selected;
}

/**
 * ArrayField Validation Object
 * @param fieldId element id
 * @param numberNeeded number to restrict to
 * @param maxOrMinOrEqual Max means not exceeding, Min means no less than, everything else is Equal to numberNeeded 
 */
function ArrayField(fieldId, numberNeeded, maxOrMinOrEqual) {
	this.fieldId = fieldId;
	this.numberNeeded = numberNeeded;
	this.maxOrMinOrEqual = maxOrMinOrEqual;
}