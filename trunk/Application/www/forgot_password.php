<?php
require_once '../includes/config.inc';
require_once 'user.inc';
require_once 'factory.inc';
require_once 'view.inc';

if (!empty($_POST)){
	$email = htmlentities($_POST['email']);
	
	try {
		$user = Factory::getView(new UserKey($email));
		
	} catch (NoResultException $e) {
		echo 'User with username: ' . $email . ' was not found';
	} catch (Exception $e) {
		echo 'Internal Error occurred, please email administrator for further assistance.';
	}
	
}

$smarty = new MySmarty($SMARTY_CONFIG);
$smarty->display('forgot_password.tpl');
	
?>