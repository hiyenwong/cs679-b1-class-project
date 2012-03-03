function lookupRsvp() {
	if (validateFields(new Array(new Field('rsvp_id')))) {
		var rsvp = $F('rsvp_id');
		
		$('status').update('<img src="'+image_url+'/loading.gif" />');
		var url = base_url + "/rsvp/getrsvp.php";
		new Ajax.Request(url, {
			parameters: {rsvp:rsvp},
			onSuccess: function(request){
				var json = Base64.decode(request.responseText).evalJSON();
				$('status').update('');
				
				remove_all_rows('guests');
				
				var img = new MyObject('img', new Array(new MyAttribute("src", image_url+"/commentsT.png")));
				var value = new MyObject('textarea', new Array(
						new MyAttribute("id", "comments"),
						new MyAttribute("name", "comments"),
						new MyAttribute("class", "inputwidth")
				), json.comment);
				
				insertRow('guests', 'comment', img, value);
				
				for (var i = 0; i < json.names.length; i++) {
					img = new MyObject('img', new Array(new MyAttribute("src", image_url+"/nameT.png")));
					value = new MyObject('input', new Array(
							new MyAttribute("type", "text"),
							new MyAttribute("id", "name_"+json.names[i].id),
							new MyAttribute("name", "name"),
							new MyAttribute("class", "inputwidth"),
							new MyAttribute("value", json.names[i].name)
					));
					
					insertRow('guests', json.names[i].id, img, value);
				}
				
				if (json.confirm == "1") {
					$('confirm').checked = "checked";
				} else {
					$('unable').checked = "checked";
				}
				
				Effect.BlindDown ('rsvp_section', {duration : 1});
			},
			onFailure: function (request) {
				$('status').update('<div class="Exception">'+request.responseText+'</div>');
			}
		});
	}
	
}

var addedGuestCount = 0;
/**
 * Add more guest input box
 */
function addMoreGuest() {
	img = new MyObject('img', new Array(new MyAttribute("src", image_url+"/nameT.png")));
	value = new MyObject('input', new Array(
			new MyAttribute("type", "text"),
			new MyAttribute("id", "name_new"),
			new MyAttribute("name", "name"),
			new MyAttribute("class", "inputwidth"),
			new MyAttribute("value", "")
	));
	
	insertRow('guests', "name_new", img, value);
	addedGuestCount++;
	
	if (addedGuestCount > 3) {
		$('addGuestButton').hide();
	}
}

/**
 * Confirm the RSVP
 */
function confirmRsvp() {
	var rsvp = $F('rsvp_id');
	
	var guests = new Array();
	var names = document.getElementsByName('name');
	for (var i = 0; i < names.length; i++) {
		if (names[i].id == "name_new") {
			guests.push({id:'new', name:names[i].value});
		} else {
			var id = names[i].id.substring(5, names[i].id.length);
			guests.push({id:id, name:names[i].value});
		}
	}
	
	var comments = $F('comments');
	var confirm = $('confirm').checked ? "true" : "false";
	
	$('status').update('<img src="'+image_url+'/loading.gif" />');
	var url = base_url + "/rsvp/confirmrsvp.php";
	new Ajax.Request(url, {
		parameters: {data:Base64.encode(Object.toJSON({rsvp:rsvp, guests:guests, comments:comments, confirm:confirm}))},
		onSuccess: function(request){
			$('status').update('<div class="Exception">'+request.responseText+'</div>');
			var json = Base64.decode(request.responseText).evalJSON();
			if (json.successful == "true") {
				$('status').update(confirm == "true" ? 
						"You are confirm to attend the wedding. Looking forward to seeing you there." :
						"Sorry to hear that you are unable to make it. We'll catch up another time.");
			} else {
				$('status').update('<div class="Exception">Something unexpected occurred, your RSVP was not successful. Please try again, or give Mary or Churk a call.</div>');
			}
		},
		onFailure: function (request) {
			$('status').update('<div class="Exception">'+request.responseText+'</div>');
		}
	});
	
}


/**
 * 
 * @param tableName
 * @param rowId
 * @param img
 * @param value
 */
function insertRow(tableName, rowId, img, value) {
	var table = $(tableName);
	var lastRow = table.insertRow(0);
	lastRow.id = rowId;

	var th = document.createElement("th");
	th.appendChild(getElementFromMyObject(img));
	lastRow.appendChild(th);
	
	var cell = lastRow.insertCell(1);
	cell.appendChild(getElementFromMyObject(value));
}

/**
 * 
 * @param myObject
 * @returns {___element1}
 */
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
 * Remove all rows from the provided table
 * @param tableName
 */
function remove_all_rows(tableName) {
	var table = $(tableName);
	for (var i = table.rows.length - 4; i >= 0; i--) {
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