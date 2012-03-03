<?php
require_once '../includes/config.inc';
require_once 'user.inc';
require_once 'factory.inc';
require_once 'view.inc';

if (!empty($_POST)){
	$email = htmlentities($_POST['email']);
	
	try {
		$results = User::getOptions(array('USERNAME'=>$email));
		
		if (sizeof($reults) > 1) {
			// This is an error where we have more than 1 user with the same email, should never happen
		} else if (sizeof($reults) === 0) {
			// This is when we can't find the user
		} else {
			$user = Factory::getView(new UserKey($results[0]['id']));
		}
		
	} catch (NoResultException $e) {
		echo 'User with username: ' . $email . ' was not found';
	} catch (Exception $e) {
		echo 'Internal Error occurred, please email administrator for further assistance.';
	}
	
}

$smarty = new MySmarty($SMARTY_CONFIG);
$smarty->display('forgot_password.tpl');
	
?>