const path = require('path');
const { exec } = require('child_process');
const shellEscape = require('shell-escape');

const debug = require('debug');
var log = debug('font-fixer');

function apply(absPath) {
	return new Promise((resolve, reject) => {
		const args = shellEscape([
			path.resolve(`${__dirname}/bin/allow_font_embed`),
			absPath
		]);
		log(args);
		exec(`${args[0]} ${args[1]}`, (err, stdout, stderr) => {
			if (err) {
				return reject(err);
			}
			resolve();
		});
	});
}

module.exports = apply;