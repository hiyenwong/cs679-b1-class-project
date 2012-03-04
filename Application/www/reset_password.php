<?php
require_once '../includes/config.inc';
require_once 'user.inc';
require_once 'factory.inc';
require_once 'view.inc';

if (!empty($_POST)){
	$email = htmlentities($_POST['email']);
	
	try {
		$results = User::getUserByUserName(array('USERNAME'=>$email));

		if (sizeof($results) > 1) {
			// This is an error where we have more than 1 user with the same email, should never happen
			$err_message = 'Internal Error occurred, please email administrator for further assistance.';
		} else if (sizeof($results) === 0) {
			// This is when we can't find the user
			$err_message = 'User with username: ' . $email . ' was not found';
		} else {
			$user = Factory::getView(new UserKey($results[0]['id']));
			$new_password_hash = $user->generateNewPassword();
		

			
		}
		
	} catch (Exception $e) {
		$err_message = 'Internal Error occurred, please email administrator for further assistance.';
	}
	
}

//$smarty = new MySmarty($SMARTY_CONFIG);
	
?>