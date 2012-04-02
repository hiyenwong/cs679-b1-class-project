<?php
	require_once '../includes/config.inc';
	require_once 'access.inc';
	require_once 'accessdeniedexception.inc';
		
	$smarty = new MySmarty($SMARTY_CONFIG);
	
	try {
		$access = new Access();
		$access->authenticate(null, null, false);
		$user = $access->getUser();
		$smarty->assign('user', $user);
	} catch (AccessDeniedException $e) {
		// Don't need to do anything, This just means user is not logged in.
	}
	
	$smarty->assign('left_menu', true);	
	$smarty->assign('about', 'about');
	$smarty->display('about.tpl');
	
?>