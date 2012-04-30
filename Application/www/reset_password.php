<?php
require_once '../includes/config.inc';
require_once 'user.inc';
require_once 'factory.inc';
require_once 'view.inc';
require_once 'access.inc';
require_once 'transaction.inc';
require_once 'toomanyfailedloginexception.inc';

$smarty = new MySmarty($SMARTY_CONFIG);

if (!empty($_POST)){
	if ($_POST['new_password'] != $_POST['verify_new_password']) {
		$smarty->assign('err_message', 'The two passwords must match');
		$smarty->display('reset_password.tpl');
	} 
	
	if (!preg_match("/((?=.*\d)(?=.*[a-z])(?=.*[A-Z])(?=.*[^a-zA-Z0-9\s]).{8,})/", $_POST['new_password'])) {
		$smarty->assign('err_message', 'Password Invalid! Must be at least 8 characters and have one lowercase, one uppercase, one number, and one special character.');
		$smarty->display('reset_password.tpl');
	}
	
	try {
		
		$username = $_GET['username'];
		$pid = $_GET['pid'];
		$result = User::checkAuthentication($username, $pid, true);

		if ($result) {
			$transaction = new Transaction(new MySqlDB());
  			$transaction->start();
  			
			$user = User::getUserByUserName($username);		
			$user->setPassword($_POST['new_password'], false);	
			$transaction->commit();
		
			$access = new Access();
            if ($access->authenticate($username, $_POST['new_password'])) {
                header ("Location: dashboard.php");
                exit();
            } 
		}else {
			echo 'fff'; 
		}
		
	} catch (Exception $e) {
		if ($transaction && !$transaction->isComplete()) {
			$transaction->rollback();
		}
		header ('HTTP/1.1 500 Internal Server Error');
		echo "Exception: " . $e->getMessage ();
	}
} else {
	$username = $_GET['username'];
	$pid = $_GET['pid'];
		
	$smarty->assign('pid', $pid);
	$smarty->assign('form_action', $BASE_URL . $_SERVER['REQUEST_URI']);
	$smarty->display('reset_password.tpl');	
}


?>