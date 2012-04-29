<?php
require_once '../includes/config.inc';
require_once 'user.inc';
require_once 'factory.inc';
require_once 'view.inc';
require_once 'transaction.inc';

if (!empty($_POST)){
	$email = htmlentities($_POST['email']);
	
	try {
		$user = User::getUserByUserName($email);

		if (sizeof($user) > 1) {
			// This is an error where we have more than 1 user with the same email, should never happen
			$err_message = 'Internal Error occurred, please email administrator for further assistance.';
		} else if (sizeof($user) === 0) {
			// This is when we can't find the user
			$err_message = 'User with username: ' . $email . ' was not found';
		} else {
  			$transaction = new Transaction(new MySqlDB());
  			$transaction->start();
  					
  			$new_password_hash = $user->generateNewPassword();
  			$user->setPassword($new_password_hash, true);
  			$transaction->commit();
  			
  			$to = $user->getUsername();
  			$subject = '.:iBudget:. Please reset your password';
  			$message = <<<BODY
Hey, we heard you forgot your iBudget password. 

Use the following link within the next 24 hours to reset your password:

<a href="{$BASE_URL}reset_password.php?username={$to}&pid={$new_password_hash}">http://localhost/cs673/cs679-b1-class-project/application/www/reset_password.php?username={$to}&pid={$new_password_hash}</a>

Thanks,
The iBudget Team
BODY;
			//echo $message; exit;
			mail($to, $subject, $message);
		}
	} catch (Exception $e) {
		if ($transaction && !$transaction->isComplete()) {
			$transaction->rollBack();
		}
		$err_message = 'Internal Error occurred, please email administrator for further assistance.';
	}
	
}

$smarty = new MySmarty($SMARTY_CONFIG);
$smarty->assign('err_message', $err_message);
$smarty->display('forgot_password.tpl');
	
?>