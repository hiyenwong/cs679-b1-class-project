<?php
	require_once '../includes/config.inc';
	require_once '../includes/user.inc';
	require_once '../includes/date.inc';
    require_once '../includes/factory.inc';
    require_once '../includes/view.inc';
	require_once '../includes/transaction.inc';
    require_once '../includes/contact.inc';
    
    $smarty = new MySmarty($SMARTY_CONFIG);
	
    if (isset($_POST['submit'])) {
	    $error = "";
		
		if (!empty($_POST)) {
			try {
				if (!empty($_POST['name'])) {
					$name = htmlentities($_POST['name']);
				}
				else {
					$error .= "Please enter your name. <br />";
				}
			
				if (!empty($_POST['email'])) {
					$email = htmlentities($_POST['email']);
				    if (!preg_match("/^[_a-z0-9]+(\.[_a-z0-9-]+)*@[a-z0-9-]+(\.[a-z0-9-]+)*(\.[a-z]{2,3})$/i", $email)){
				  		$error .= "Please enter a valid email address. <br/>";
					}
				}
				else {
					$error .= "Please enter a valid email address. <br />";
				}
			
				if (!empty($_POST['message'])) {
					$message = htmlentities($_POST['message']);
				}
				else {
					$error .= "Please enter a message. <br />";
				}
						
				if (empty($error)) {
					$from = 'From: ' . $name . ' <' . $email . '>';
					$to = "qlahnn@bu.edu";
					$subject = "iBuget Contact Form Message";
					$content = $name . " has sent the iBudget team a message: \n" . $message;
					mail($to,$subject,$content,$from);
				}
						
				// inserting into table contact				
				$t = new Transaction(new MySqlDB());
				$t->start();
				$u = false;
				try {
					$u = Factory::getView(new UserKey($user_id));
				} catch (NoResultException $e) {
					// no user logon
					$u = false;
				} catch (Exception $e) {
				  echo 'Internal Error occurred, please email administrator for further assistance.';
				}
				
				// check to see if user's email exists in database
				if (!$u) {
					$results = User::getOptions(array('USERNAME'=>$email));
					foreach ($results as $id => $val) {
						$u = Factory::getView(new UserKey($id));
						break;
					}
				}
				//if (empty($u)) {
					//$u = Factory::createView(new UserKey());
				//}
			
				$contact = Factory::createView(new ContactKey());
				if ($u) {
					$contact.setUser($u);
				}
				
				$date = new Date();
				$contact->setEmail($email);
				$contact->setContent($message);
				$contact->setDateSubmitted($date);
				
				// $date = new Date();
				// $t->setName($name);
				//$u->setUser($u);
				//$u->setEmail($email);
				//$u->setDateSubmitted($date->getTimestamp());
				//$u->setContent($message);
		   
				$t->commit();

			} catch (Exception $e) {
				if ($t && !$t->isCompleted()) {
    				$t->rollBack();
				}
				echo $error;
			}
		}
	}
	
	$smarty->display('contact.tpl');
?>