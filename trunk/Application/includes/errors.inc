<?php
	require_once 'config.inc';

	$old_error_handler = set_error_handler ('admin_error_handler');
	$old_exception_handler = set_exception_handler ('admin_exception_handler');
	$old_error_reporting = ini_get ('error_reporting');
	$smarty = new MySmarty($SMARTY_CONFIG);

	error_reporting (($old_error_reporting) | (E_USER_ERROR | E_USER_WARNING | E_USER_NOTICE));

	/**
	 * Error handler to override PHPs with set_error_handler.
	 */
	function admin_error_handler ($error_level, $error_message, $error_file, $error_line) {
		global $smarty;
		$menu = navmenu::getMainNavMenu();
		$smarty->assign ('menu', $menu);

		global $old_error_reporting;

		switch ($error_level) {

			// fatal error (should flush output and take to single page)a
			case E_USER_ERROR:
				$smarty->assign ('error_message', $error_message);
				$smarty->display ('error.tpl');
				exit (1);
			break;

			// user error
			case E_USER_WARNING:
				$smarty->append ('warnings', $error_message);
			break;

			case E_USER_NOTICE:
				$smarty->append ('notices', $error_message);
			break;

			default:
				// normal PHP level errors
				switch ($error_level) {
					case E_WARNING:
						$error_type = 'Warning';
					break;

					case E_NOTICE:
						$error_type = 'Notice';
					break;

					case E_RECOVERABLE_ERROR:
						$error_type = 'Recoverable Error';
					break;

					default:
						$error_type = 'Unknown';
					break;
				}

				$message = sprintf ("%s: %s in %s on line %d", $error_type, $error_message, $error_file, $error_line);
				if (ini_get ('log_errors')) {
					if ($error_level & $old_error_reporting) {
						error_log ($message);
					}
				}
			break;
		}
	}

	function admin_exception_handler ($exception) {
		global $smarty;
		$menu = navmenu::getMainNavMenu();
		$smarty->assign ('menu', $menu);
		$smarty->assign ('exception', $exception);
		$smarty->display ('exception.tpl');

		exit (1);
	}

?>