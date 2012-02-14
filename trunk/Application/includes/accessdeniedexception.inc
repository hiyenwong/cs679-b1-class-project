<?php
/**
 * $Id: accessdeniedexception.inc,v 1.2 2010/06/14 11:05:50 cyl2478 Exp $
 */

class AccessDeniedException extends Exception {

	public function __construct ($message, $code = 0) {
		parent::__construct ($message, $code);
	}

}
?>
