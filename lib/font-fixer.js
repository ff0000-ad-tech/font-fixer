const fs = require('fs');
const path = require('path');
const { exec } = require('child_process');
const shellEscape = require('shell-escape');
const ncp = require('ncp');

const debug = require('debug');
var log = debug('font-fixer');

function apply(absPath) {
	return new Promise((resolve, reject) => {
		const fixedPath = `${path.dirname(absPath)}/${path.basename(absPath).split('.')[0]}__drm-stripped${path.extname(absPath)}`;
		if (fs.existsSync(fixedPath)) {
			fs.unlinkSync(fixedPath);
		}
		ncp(absPath, fixedPath, (err) => {
			if (err) {
				return reject(err);
			}
			const args = shellEscape([
				path.resolve(`${__dirname}/../bin/allow_font_embed`),
				fixedPath
			]);
			exec(args, (err, stdout, stderr) => {
				if (err) {
					return reject(err);
				}
				log('Result:', fixedPath);
				resolve();
			});

		});
	});
}

module.exports = apply;