<?php
require_once '../includes/config.inc';
require_once 'user.inc';
require_once 'factory.inc';
require_once 'view.inc';
require_once 'transaction.inc';

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
			
  			try{
				$transaction = new Transaction(new MySqlDB());
			 	$transaction->start();
			 	
			 	$user = Factory::getView(new UserKey($results[0]['id']));
				$new_password_hash = $user->generateNewPassword();
				
				$to = $user->getUsername();
				$subject = '.:iBudget:. Please reset your password';
				$message = <<<BODY
Hey, we heard you forgot your iBudget password. 

Use the following link within the next 24 hours to reset your password:

<a href="http://localhost/cs673/cs679-b1-class-project/application/www/reset_password/{$to}/{$new_password_hash}">http://localhost/cs673/cs679-b1-class-project/application/www/reset_password/{$to}/{$new_password_hash}</a>

Thanks,
The iBudget Team
BODY;
				$transaction->commit();
				//echo $message; exit;
				mail($to, $subject, $message);
	  		} catch (Exception $e) {
			  if ($transaction && !$transaction->isComplete()) {
			    $transaction->rollBack();
			  }
			}
		}
	} catch (Exception $e) {
		$err_message = 'Internal Error occurred, please email administrator for further assistance.';
	}
	
}

$smarty = new MySmarty($SMARTY_CONFIG);
$smarty->assign('err_message', $err_message);
$smarty->display('forgot_password.tpl');
	
?>