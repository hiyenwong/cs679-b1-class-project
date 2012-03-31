<?php

require_once 'config.inc';
require_once 'user.inc';
require_once 'date.inc';
require_once 'accessdeniedexception.inc';

class Access {

	private $user;

	public function __construct () {
		session_start();
	}

	public function authenticate($username = null, $password = null, $forward = true) {
		if ($username == null) {
			// Assume logged in and use session data to authenticate
			if (array_key_exists('user', $_SESSION) && $_SESSION['user'] != '') {
				$user = $_SESSION['user'];
				$time = $_SESSION['time'];
				$token = $_SESSION['token'];
				if (sha1($user.$time) == $token) {
					$this->user = $user;
					return true;
				} else {
					if ($forward) {
						$this->forwardLogin();
					} else {
						throw new AccessDeniedException("access is denied");
					}
				}

			} else {
				if ($forward) {
					$this->forwardLogin();
				} else {
					throw new AccessDeniedException("access is denied");
				}
			}
		} else {
			if (User::checkAuthentication($username, $password)) {
				$_SESSION['user'] = $username;
				$time = new Date();
				$_SESSION['time'] = $time->getTime();
				$_SESSION['token'] = sha1($username.$time->getTime());
				$this->user = $username;
				return true;
			} else {
				return false;
				//$this->forwardLogin();
			}
		}
	}

	private function forwardLogin() {
		global $LOGIN_URL;

		$url = $LOGIN_URL . "?ref=" . base64_encode ($_SERVER ['REQUEST_URI']);

		if (headers_sent ()) {
			trigger_error ('Please <a href="' . $url . '">Login</a> before continuing.', E_USER_ERROR);
		} else {
			header ("Location: " . $url);
			exit ();
		}
	}

	/**
	 * Check if a user is logged in.
	 */
	public function isLoggedIn () {
		if (!isset($_SESSION['user'])){
			return false;
		} else {
			$user = $_SESSION['user'];
			$time = $_SESSION['time'];
			$token = $_SESSION['token'];

			return $token == sha1($user.$time);
		}
	}

	/**
	 * Get the user object. Will force person to login, handle ssofs, etc.
	 */
	public function getUser () {

		// if we have the user object setup then we're all set
		if (isset ($this->user)) {
			return User::getUserByUserName($this->user);
		}

		// contact ssofs doing authc only and not allowing guest
		// this will force them to login if they have not yet
		$this->authenticate ();

		// at this point we will either have the user form checkSSOFS
		return User::getUserByUserName($this->user);
	}




	/********************************************************************************/

}
?>