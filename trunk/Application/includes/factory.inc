<?php

require_once 'key.inc';
require_once 'cache.inc';

function __autoload ($name) {
	include_once strtolower ($name) . '.inc';
}

abstract class Factory {

	private static $stack = array ();

	public static function createView (Key $key) {

		if (!$key->isNew ()) {
			throw new Exception (__CLASS__ . ' ' . __METHOD__ . ' must be given a new empty Key.');
		}

		$class = $key->getClass ();
		$view = new $class ($key);

		$cache = Cache::getCache ();
		$cache->registerView ($key, $view);

		return $view;
	}

	public static function getView (Key $key) {

		$cache = Cache::getCache ();

		$view = $cache->getView ($key);

		if (!$view) {

			if (array_key_exists ($key->__toString (), self::$stack)) {
				return self::$stack [$key->__toString ()];
			}

			$class = $key->getClass ();
			$view = new $class ($key);

			self::$stack [$key->__toString ()] = $view;
			$view->read ();
			unset (self::$stack [$key->__toString ()]);

			$cache->registerView ($key, $view);
		}

		return $view;
	}
}
?>