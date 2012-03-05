<?php
require_once '../includes/config.inc';
require_once 'user.inc';
require_once 'factory.inc';
require_once 'view.inc';
require_once 'transaction.inc';

$smarty = new MySmarty($SMARTY_CONFIG);

if (!empty($_POST)){
	
	if ($_POST['new_password'] != $_POST['verify_new_password']) {
		$err_message = 'The two passwords must match';
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
		}
		
	} catch (Exception $e) {
		//handle exception
	}
	
	$smarty->display('reset_password.tpl');
} else {
	$username = $_GET['username'];
	$pid = $_GET['pid'];
		
	$smarty->assign('username', $username);
	$smarty->assign('pid', $pid);
	$smarty->display('reset_password.tpl');	
}


?>