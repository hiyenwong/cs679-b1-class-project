<?php
require_once '../includes/config.inc';
require_once 'user.inc';
require_once 'factory.inc';
require_once 'view.inc';
require_once 'transaction.inc';

$smarty = new MySmarty($SMARTY_CONFIG);

if (!empty($_POST)){
	
	if (!preg_match("/((?=.*\d)(?=.*[a-z])(?=.*[A-Z])(?=.*[^a-zA-Z0-9\s]).{8,})/", $_POST['new_password'])) {
		$smarty->assign('err_message', 'Password Invalid! Must be at least 8 characters and have one lowercase, one uppercase, one number, and one special character.');
        $smarty->display('reset_password.tpl');
	}
	
	if ($_POST['new_password'] != $_POST['verify_new_password']) {
		$err_message = 'The two passwords must match';
		//header ("Location: " . $requestedUrl);
		$smarty->assign('err_message', $err_message);
		$smarty->display('reset_password.tpl');
	} 
	
	//additional checks that the password is at least 8 chars etc
	try {
		$username = $_POST['username'];
		$pid = $_POST['pid'];
	
		$result = User::checkAuthentication($username, $pid, true);
		if ($result) {
			$transaction = new Transaction(new MySqlDB());
  			$transaction->start();
  			
			$results = User::getUserByUserName($username);
			foreach ($results as $row) {
  				// We know results has only one record so it is ok to foreach on this and break
  				$user = Factory::getView(new UserKey($row['id']));
  				break;
  			}		
			$new_password = $user->setPassword($_POST['new_password'], false);	
			$transaction->commit();
		 	header( 'Location: userpage.php' );
			exit();
		}
		
	} catch (Exception $e) {
		//handle exception
	}
	
	//$smarty->display('reset_password.tpl');
} else {
	$username = $_GET['username'];
	$pid = $_GET['pid'];
		
	$smarty->assign('username', $username);
	$smarty->assign('pid', $pid);
	$smarty->assign('form_action', $_SERVER['REQUEST_URI']);
	$smarty->display('reset_password.tpl');	
}


?>