<?php
	session_start();
	require_once '../includes/config.inc';
	require_once '../includes/user.inc';

	$smarty = new MySmarty($SMARTY_CONFIG);

	$user_temp = User::getUserByUserName($_SESSION['username']);
	$user = UserSource::getSource();
	$user = $user->read(array('ID'=>$user_temp[0]['id']));

	$smarty->assign('username', $user['first_name']);
	$smarty->assign('left_menu', true);
	$smarty->display('userpage.tpl');
	
?>