//
// AS3DTools
//
// (C) 2021-2023 modeco80 <lily.modeco80@protonmail.ch>
//
// SPDX-License-Identifier: GPL-3.0-or-later
//

#include <As3dpakConfig.hpp>

#include <tasks/InfoTask.hpp>
#include <tasks/ExtractTask.hpp>
#include <tasks/CreateTask.hpp>

#include <argparse/argparse.hpp>

int main(int argc, char** argv) {
	argparse::ArgumentParser parser("as3dpak", AS3DPAK_VERSION_STR);
	parser.add_description("as3dpak (Air Strike 3D APK Multi-Tool) v" AS3DPAK_VERSION_STR);

	argparse::ArgumentParser infoParser("info", AS3DPAK_VERSION_STR, argparse::default_arguments::help);
	infoParser.add_description("Print information about an APK file.");
	infoParser.add_argument("input")
		.help("Input archive")
		.metavar("ARCHIVE");
	infoParser.add_argument("--verbose")
		.help("Increase information output verbosity (print a list of files).")
		.default_value(false)
		.implicit_value(true);

	argparse::ArgumentParser extractParser("extract", AS3DPAK_VERSION_STR, argparse::default_arguments::help);
	extractParser.add_description("Extract an APK file.");
	extractParser.add_argument("-d", "--directory")
				.default_value("")
				.metavar("DIRECTORY")
				.help("Directory to extract to.");
	extractParser.add_argument("input")
				.help("Input archive")
				.metavar("ARCHIVE");
	extractParser.add_argument("--verbose")
			.help("Increase extraction output verbosity")
			.default_value(false)
			.implicit_value(true);

	argparse::ArgumentParser createParser("create", AS3DPAK_VERSION_STR, argparse::default_arguments::help);
	createParser.add_description("Create an APK file.");
	createParser.add_argument("-d", "--directory")
				.required()
				.metavar("DIRECTORY")
				.help("Directory to create archive from");
	createParser.add_argument("output")
				.required()
				.help("Output archive")
				.metavar("ARCHIVE");
	createParser.add_argument("--verbose")
				.help("Increase creation output verbosity")
				.default_value(false)
				.implicit_value(true);


	parser.add_subparser(infoParser);
	parser.add_subparser(extractParser);
	parser.add_subparser(createParser);

	try {
		parser.parse_args(argc, argv);
	} catch(std::runtime_error& error) {
		std::cout << error.what() << '\n' << parser;
		return 1;
	}

	// Run the given task

	if(parser.is_subcommand_used("extract")) {
		as3dpak::tasks::ExtractTask task;
		as3dpak::tasks::ExtractTask::Arguments args;

		args.verbose = extractParser.get<bool>("--verbose");
		args.inputPath = as3dpak::fs::path(extractParser.get("input"));

		if(extractParser.is_used("--directory")) {
			args.outputDirectory = as3dpak::fs::path(extractParser.get("--directory"));
		} else {
			// Default to the basename appended to current path
			// as a "relatively sane" default path to extract to.
			// Should be okay.
			args.outputDirectory = as3dpak::fs::current_path() / args.inputPath.stem();
		}

		std::cout << "Input APK: " << args.inputPath << '\n';
		std::cout << "Output Directory: " << args.outputDirectory << '\n';

		return task.Run(std::move(args));
	}

	if(parser.is_subcommand_used("info")) {
		as3dpak::tasks::InfoTask task;
		as3dpak::tasks::InfoTask::Arguments args;

		args.verbose = infoParser.get<bool>("--verbose");
		args.inputPath = as3dpak::fs::path(infoParser.get("input"));

		return task.Run(std::move(args));
	}

	if(parser.is_subcommand_used("create")) {
		as3dpak::tasks::CreateTask task;
		as3dpak::tasks::CreateTask::Arguments args;

		args.verbose = createParser.get<bool>("--verbose");
		args.inputDirectory = as3dpak::fs::path(createParser.get("--directory"));
		args.outputFile = as3dpak::fs::path(createParser.get("output"));

		if(!as3dpak::fs::is_directory(args.inputDirectory)) {
			std::cout << "Error: Provided input isn't a directory\n" << createParser;
			return 1;
		}

		return task.Run(std::move(args));
	}

	return 0;
}