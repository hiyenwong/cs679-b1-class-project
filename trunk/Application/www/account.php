<?php
	session_start();
	require_once '../includes/config.inc';
	require_once 'user.inc';
	require_once 'access.inc';
	require_once 'transaction.inc';
	
	$smarty = new MySmarty($SMARTY_CONFIG);
	
	try {
		$access = new Access();
		$access->authenticate();
		$user = $access->getUser();		
		$smarty->assign('user', $user);
		$smarty->assign('left_menu', true);
	} catch (AccessDeniedException $e) {
		trigger_error('Access Denied');
	} catch (Exception $e) {
		trigger_error('An error has occurred, please try again in a few minutes');
	}
	if (isset($_POST['new_password']) && isset($_POST['verify_new_password'])) {
	if (!preg_match("/((?=.*\d)(?=.*[a-z])(?=.*[A-Z])(?=.*[^a-zA-Z0-9\s]).{8,})/", $_POST['new_password'])) {
			$smarty->assign('err_message', 'Password Invalid! Must be at least 8 characters and have one lowercase, one uppercase, one number, and one special character.');
	        //$smarty->display('account.tpl');
	}
	else if (isset($_POST['update_password'])){
		if ($_POST['new_password'] != $_POST['verify_new_password']) {
			$smarty->assign('err_message', 'The two passwords must match');
			//$smarty->display('account.tpl');
		} 
	else {
		try {	
			$transaction = new Transaction(new MySqlDB());
	  		$transaction->start();
	  		
			//$user = User::getUserByUserName($username);		
			$user->setPassword($_POST['new_password'], false);	
			$transaction->commit();
		} catch (Exception $e) {
			if ($transaction && !$transaction->isComplete()) {
				$transaction->rollback();
			}
			header ('HTTP/1.1 500 Internal Server Error');
			echo "Exception: " . $e->getMessage ();
		}	
	} 
	}
	}
	if (isset($_POST['update_name'])) {
		$transaction = new Transaction(new MySqlDB());
  		$transaction->start();
  		if (empty($_POST['firstName']))
  			$smarty->assign('err_message', 'Firstname cannot be empty.');
  		else
			$user->setFirstName($_POST['firstName']);
		if (empty($_POST['lastName']))
			$smarty->assign('err_message', 'Lastname cannot be empty.');
		else
			$user->setLastName($_POST['lastName']);
		$transaction->commit();
	}
	
	$smarty->display('account.tpl');
?>