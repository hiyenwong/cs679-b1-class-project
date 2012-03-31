<?php
	require_once '../includes/config.inc';
	require_once 'user.inc';
	require_once 'access.inc';
	require_once 'date.inc';
	require_once 'factory.inc';
	require_once 'view.inc';
	require_once 'transaction.inc';
	require_once 'contact.inc';

	if (isset($_POST['submit'])) {
		$user = false;

		try {
			$access = new Access();
			$access->authenticate(null, null, false);
			$user = $access->getUser();
		} catch (AccessDeniedException $e) {
			// Don't need to do anything, This just means user is not logged in.
		}

		try {
			$name = isset($_REQUEST['name']) ? htmlentities($_REQUEST['name']) : false;
			$email = isset($_REQUEST['email']) && preg_match("/^[_a-z0-9]+(\.[_a-z0-9-]+)*@[a-z0-9-]+(\.[a-z0-9-]+)*(\.[a-z]{2,3})$/i", $_REQUEST['email']) ?
				htmlentities($_REQUEST['email']) : false;
			$message = isset($_REQUEST['message']) ? htmlentities($_REQUEST['message']) : false;

			// inserting into table contact
			$transaction = new Transaction(new MySqlDB());
			$transaction->start();

			if (!$user) {
				// User is not logged in, so trying to find user by his provided email
				$temp = User::getUserByUserName($email);
				if ($temp !== null) {
					$user = $temp;
				}
			}

			$contact = Factory::createView(new ContactKey());
			if ($user) {
				$contact.setUser($user);
			}

			$contact->setName($name);
			$contact->setEmail($email);
			$contact->setContent($message);
			$contact->setDateSubmitted(new Date());
			$transaction->commit();

		} catch (Exception $e) {
			if ($transaction && !$transaction->isComplete()) {
				$transaction->rollBack();
			}
			echo "<PRE>A error had occured: " . $e->getMessage() . "\n" . $e->getTraceAsString() . "\n</PRE>";
		}
	} else {
		$smarty->display('contact.tpl');
		$smarty = new MySmarty($SMARTY_CONFIG);
	}
?>