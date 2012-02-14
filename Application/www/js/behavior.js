/*
Copyright (c)
  2004, Simon Willison
  2005, Ben Nolan
  2005, Michael Schuerig
 All rights reserved.

Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this list
of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice, this
list of conditions and the following disclaimer in the documentation and/or
other materials provided with the distribution.

3. Neither the name of the <ORGANIZATION> nor the names of its contributors may be
used to endorse or promote products derived from this software without specific
prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
/*
   Behavior 1.1

   Michael Schuerig, michael@schuerig.de, 2005
   http://www.schuerig.de/michael/javascripts/

   Heavy refactoring, support for child selectors, multiple class names,
   :first-child pseudo class and unit tests.
   Renamed (ever so slightly) to avoid (some) confusion.
*/
/*
   Behaviour v1.0 by Ben Nolan, June 2005. Based largely on the work
   of Simon Willison (see comments by Simon below).

   Description:

   	Uses css selectors to apply javascript behaviours to enable
   	unobtrusive javascript in html documents.

   Usage:

	var myrules = {
		'b.someclass' : function(element){
			element.onclick = function(){
				alert(this.innerHTML);
			}
		},
		'#someid u' : function(element){
			element.onmouseover = function(){
				this.innerHTML = "BLAH!";
			}
		}
	);

	Behaviour.register(myrules);

	// Call Behaviour.apply() to re-apply the rules (if you
	// update the dom, etc).

   License:

   	My stuff is BSD licensed.

   More information:

   	http://ripcord.co.nz/behaviour/
*/
/*
   The original version of document.getElementsBySelector is Copyright (C) Simon Willison 2004.
   http://simon.incutio.com/js/getElementsBySelector.js

   [MS: Simon agreed by mail to BDS licensing]

   document.getElementsBySelector(selector)
   - returns an array of element objects from the current document
     matching the CSS selector. Selectors can contain element names,
     class names and ids and can be nested. For example:

       elements = document.getElementsBySelect('div#main p a.external')

     Will return an array of all 'a' elements with 'external' in their
     class attribute that are contained inside 'p' elements that are
     contained inside the 'div' element which has id="main"

   New in version 0.4: Support for CSS2 and CSS3 attribute selectors:
   See http://www.w3.org/TR/css3-selectors/#attribute-selectors

   Version 0.4 - Simon Willison, March 25th 2003
   -- Works in Phoenix 0.5, Mozilla 1.3, Opera 7, Internet Explorer 6, Internet Explorer 5 on Windows
   -- Opera 7 fails
*/

var Behavior = {
  Version: '1.1.1',

  debug: false,
  useCssQuery: false,

  list: [],

  register: function(sheet) {
    Behavior.list.push(sheet);
  },

  start: function() {
    Event.observe(window, 'load', Behavior.apply);
  },

  apply: function() {
    var startTime = new Date();
    for (var h = 0; sheet = Behavior.list[h]; h++) {
      for (var selector in sheet) {
        var bhv = sheet[selector];
        if (!bhv) continue;
        var elements = document.getElementsBySelector(selector);
        for (var i = 0; element = elements[i]; i++) {
          bhv(element);
        }
      }
    }
    if (Behavior.debug) {
      alert('Applying Behaviors took: ' + (new Date() - startTime) + 'ms');
    }
    if (Behavior.useCssQuery) {
      cssQuery.clearCache();
    }
  },

  extractOptions: function(element) {
    var classNames = (element.className || '').split(' ');
    var options = {};
    for (var i = 1; i < arguments.length; i++) {
      var arg = arguments[i];
      var value = Behavior._decodeArgument(arg, classNames);
      if (value) {
        options[arg] = value;
      }
    }
    return options;
  },

  _decodeArgument: function(arg, classNames) {
    var boolArg = arg;
    var keyArg = arg + ':';
    var len = classNames.length;
    for (var i = 0; i < len; i++) {
      var cn = classNames[i];
      if (cn == boolArg) {
        return true;
      } else if (cn.indexOf(keyArg) === 0) {
        var encValue = cn.split(':', 2)[1];
        if (encValue) {
          return eval(decodeURIComponent(encValue));
        }
      }
    }
    return undefined;
  }
};

Behavior.start();

if (Behavior.useCssQuery) {
  cssQuery.caching = true;
  document.getElementsBySelector = cssQuery;
} else {

  document.getElementsBySelector = function() {

    if (!document.getElementsByTagName) {
      return function() { return []; };
    }

    function addToSet(set, elements) {
      var elementsLen = elements.length;
      for (var i = 0; i < elementsLen; i++) {
        var el = elements[i];
        var isInSet = false;
        var setLen = set.length;
        for (var j = 0; !isInSet && j < setLen; j++) {
          if (set[j] === el) {
            isInSet = true;
          }
        }
        if (!isInSet) {
          set.push(el);
        }
      }
    }

    function findById(currentContext, token) {
      var items = token.split('#');
      var tagName = items[0].toUpperCase();
      var id = items[1];
      var element = document.getElementById(id);
      if (tagName && element.tagName != tagName) {
        return [];
      }
      return [ element ];
    }

    function filterByClassNames(currentContext, classNames) {
      if (currentContext.length === 0 || classNames.length === 0) {
        return [];
      }
      classNameREs = [];
      for (var i = 0; i < classNames.length; i++) {
        classNameREs.push(new RegExp('\\b' + classNames[i] + '\\b'));
      }
      var found = [];
      for (var i = 0; i < currentContext.length; i++) {
        var cn = currentContext[i].className;
        if (cn) {
          var matches = true;
          for (var j = 0; matches && j < classNames.length; j++) {
            matches = classNameREs[j].test(cn);
          }
          if (matches) {
            found.push(currentContext[i]);
          }
        }
      }
      return found;
    }

    function filterByAttribute(currentContext, attrName, attrOperator, attrValue) {
      var found = [];
      var checkFunction;
      switch (attrOperator) {
        case '=': // Equality
          checkFunction = function(e) { return (e.getAttribute(attrName) == attrValue); };
          break;
        case '~': // Match one of space seperated words
          checkFunction = function(e) { return (e.getAttribute(attrName).match(new RegExp('\\b'+attrValue+'\\b'))); };
          break;
        case '|': // Match start with value followed by optional hyphen
          checkFunction = function(e) { return (e.getAttribute(attrName).match(new RegExp('^'+attrValue+'-?'))); };
          break;
        case '^': // Match starts with value
          checkFunction = function(e) { return (e.getAttribute(attrName).indexOf(attrValue) == 0); };
          break;
        case '$': // Match ends with value - fails with "Warning" in Opera 7
          checkFunction = function(e) { return (e.getAttribute(attrName).lastIndexOf(attrValue) == e.getAttribute(attrName).length - attrValue.length); };
          break;
        case '*': // Match ends with value
          checkFunction = function(e) { return (e.getAttribute(attrName).indexOf(attrValue) > -1); };
          break;
        default :
          // Just test for existence of attribute
          checkFunction = function(e) { return e.getAttribute(attrName); };
      }
      found = [];
      for (var i = 0; i < currentContext.length; i++) {
        if (checkFunction(currentContext[i])) {
          found.push(currentContext[i]);
        }
      }
      return found;
    }

    function filterFirstChildren(currentContext) {
      var found = [];
      for (var i = 0; i < currentContext.length; i++) {
        var child = currentContext[i];
        var children = child.parentNode.childNodes;
        for (var j = 0; j < children.length; j++) {
          var otherChild = children[j];
          if (otherChild.nodeType == 1) {
            if (child === otherChild) {
              found.push(child);
            }
            break;
          }
        }
      }
      return found;
    }

    function findByTagName(currentContext, tagName, childrenOnly) {
      if (!tagName) {
        tagName = '*';
      } else {
        tagName = tagName.toUpperCase();
      }
      var found = [];
      for (var i = 0; i < currentContext.length; i++) {
        var el = currentContext[i];
        var elements;
        if (childrenOnly) {
          var children = el.childNodes;
          elements = [];
          for (var j = 0; j < children.length; j++) {
            var child = children[j];
            if (child.nodeType == 1 && (tagName == '*' || child.tagName == tagName)) {
              elements.push(child);
            }
          }
        } else {
          if (tagName == '*') {
            // Returns all children of element. Workaround required for IE5/Windows. Ugh.
            elements = el.all ? el.all : el.getElementsByTagName('*');
          } else {
            elements = currentContext[i].getElementsByTagName(tagName);
          }
        }
        addToSet(found, elements);
      }
      return found;
    }

    function getElementsBySelector(selector) {
      var tokens = selector.replace(/\s*:/, ':').replace(/\s+>\s+/, ' >').split(' ');

      var currentContext = [ document ];

      for (var i = 0; i < tokens.length; i++) {
        var token = tokens[i].replace(/^\s+/,'').replace(/\s+$/,'');;
        var childrenOnly = token.indexOf('>') != -1;
        if (childrenOnly) {
          token = token.substring(1);
        }

        if (token.indexOf('#') > -1) {
          currentContext = findById(currentContext, token);
          continue;
        }

        var tagName = token;
        var classNames;
        var attrName;
        var attrOperator;
        var attrValue;
        var firstChild = false;

        if (/:first-child$/.test(token)) {
          token = token.slice(0, -(':first-child'.length));
          firstChild = true;
        }

        if (token.match(/^(.*)\[(\w+)([=~\|\^\$\*]?)=?"?([^\]"]*)"?\]$/)) {
          token = RegExp.$1;
          attrName = RegExp.$2;
          attrOperator = RegExp.$3;
          attrValue = RegExp.$4;
        }

        if (token.indexOf('.') > -1) {
          classNames = token.split('.');
          token = classNames.shift();
        }

        currentContext = findByTagName(currentContext, token, childrenOnly);
        if (classNames) {
          currentContext = filterByClassNames(currentContext, classNames);
        }
        if (attrName) {
          currentContext = filterByAttribute(currentContext, attrName, attrOperator, attrValue);
        }

        if (firstChild) {
          currentContext = filterFirstChildren(currentContext);
        }
      }
      return currentContext;
    }

    return getElementsBySelector;
  }();
}
