<?php
	require_once '../includes/config.inc';
	require_once 'access.inc';
	require_once 'accessdeniedexception.inc';
	
	try {
		$smarty = new MySmarty($SMARTY_CONFIG);
		
		try {
			$access = new Access();
			$access->authenticate(null, null, false);
			$user = $access->getUser();
			$smarty->assign('user', $user);
		} catch (AccessDeniedException $e) {
			// Don't need to do anything, This just means user is not logged in.
		}
		
		$smarty->assign('homepage', 'homepage');
		$smarty->assign('left_menu', 'none'); //quick and dirty way
		$smarty->display('index.tpl');
		
	} catch (AccessDeniedException $e) {
		trigger_error('Access Denied');
	} catch (Exception $e) {
		trigger_error('An error has occurred, please try again in a few minutes');
	}
	
?>