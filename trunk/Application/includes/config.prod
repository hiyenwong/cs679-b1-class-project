<?php

	$GLOBALS["_start_time"] = microtime (true);
	date_default_timezone_set('America/New_York');

	$DBHOST					= "churkl.no-ip.com";
	$DBNAME					= "ibudget";
	$DBUSER					= "ibudget";
	$DBPASSWD				= "ibudget";

	$VERSION = 				"TEST";
	$DISABLE_EMAIL = 		true;

	$INSTALL_DIR = 			"/home1/complexf/src/iBudget/Application";
	$ATTACHMENT_ROOT = 		$INSTALL_DIR . "/attachment";
	$INCLUDE_PATH = 		$INSTALL_DIR . "/includes";
	$TEMPLATE_DIR = 		$INSTALL_DIR . "/templates";
	$COMPILE_DIR = 			$INSTALL_DIR . "/compiled";
	$CACHE_DIR = 			$INSTALL_DIR . "/cache";
	$SMARTY_DIR = 			$INSTALL_DIR . "/smarty";

	$BASE_URL = 			"";
	$IMAGE_URL = 			$BASE_URL . "/images";
	$STYLE_URL = 			$BASE_URL . "/style";
	$JS_URL	= 				$BASE_URL . "/js";
	$LOGIN_URL = 			$BASE_URL . '/admin/login.php';
	$LOGOUT_URL = 			$BASE_URL . '/admin/logout.php';
	$CHANGE_PASSWORD_URL = 	$BASE_URL . '/admin/changepw.php';
	$RESET_PASSWORD_URL	= 	$BASE_URL . '/admin/resetpw.php';
	$ACCESS_DENIED_URL = 	$BASE_URL . '/admin/denied.php';
	$REDIRECT_URL = 		$BASE_URL . '/admin/redirect.php';
	$SYSTEM_URL = 			(isset($_SERVER ["HTTPS"]) ? "https://" : "http://") . $_SERVER ["SERVER_NAME"];

	/* include path */
	set_include_path (get_include_path () . PATH_SEPARATOR . $INCLUDE_PATH);

	$SMARTY_CONFIG = array(
		"TEMPLATE" => 			$TEMPLATE_DIR,
		"COMPILE" => 			$COMPILE_DIR,
		"CACHE" => 				$CACHE_DIR,
		"CONFIG" => 			$INCLUDE_PATH,
		"VERSION" => 			$VERSION,
		"BASE_URL" => 			$BASE_URL,
		"IMAGE_URL" => 			$IMAGE_URL,
		"STYLE_URL" => 			$STYLE_URL,
		"JS_URL" => 			$JS_URL,
		"SYSTEM_URL" => 		$SYSTEM_URL,
		"REDIRECT_URL" => 		$REDIRECT_URL,
		"LOGIN_URL" => 			$LOGIN_URL,
		"LOGOUT_URL" => 		$LOGOUT_URL,
		"WEBMASTER" => 			"admin@simplefunctions.com",
		"MAX_UPLOAD_SIZE" => 	2147000000,
		"MAX_UPLOAD_PARSED" => 	"2.1 GB",
		"MAX_ATTACHMENTS" => 	6,
		"CACHE" => 				false
	);

	$IS_IE = !(stristr($_SERVER['HTTP_USER_AGENT'], "Mozilla") &&
				!(stristr ($_SERVER['HTTP_USER_AGENT'], "compatible")));

	function error_page ($message) {
		$weblink = '<a href="http://iBudget.simplefunctions.com">iBudget Home Page</a>';
		echo '<html>
				<head>
					<link rel="stylesheet" href="'.$STYLE_URL.'/ibudget.css" type="text/css" />
					<title>Error</title>
				</head>
				<body>
					<h2>Error</h2>' . $message . '
					<p>If you believe you have reached this page in error please contact the ' . $weblink . '.</p>
				</body>
			</html>';
	}

	require_once 'mysmarty.inc';

?>
