{
	"patcher" : 	{
		"fileversion" : 1,
		"appversion" : 		{
			"major" : 7,
			"minor" : 3,
			"revision" : 4,
			"architecture" : "x64",
			"modernui" : 1
		}
,
		"rect" : [ 100.0, 100.0, 703.0, 559.0 ],
		"bglocked" : 0,
		"openinpresentation" : 0,
		"default_fontsize" : 12.0,
		"default_fontface" : 0,
		"default_fontname" : "Arial",
		"gridonopen" : 1,
		"gridsize" : [ 5.0, 5.0 ],
		"gridsnaponopen" : 1,
		"objectsnaponopen" : 1,
		"statusbarvisible" : 2,
		"toolbarvisible" : 1,
		"lefttoolbarpinned" : 0,
		"toptoolbarpinned" : 0,
		"righttoolbarpinned" : 0,
		"bottomtoolbarpinned" : 0,
		"toolbars_unpinned_last_save" : 0,
		"tallnewobj" : 0,
		"boxanimatetime" : 200,
		"enablehscroll" : 1,
		"enablevscroll" : 1,
		"devicewidth" : 0.0,
		"description" : "",
		"digest" : "",
		"tags" : "",
		"style" : "",
		"subpatcher_template" : "",
		"showrootpatcherontab" : 0,
		"showontab" : 0,
		"boxes" : [ 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"id" : "obj-15",
					"maxclass" : "newobj",
					"numinlets" : 0,
					"numoutlets" : 0,
					"patcher" : 					{
						"fileversion" : 1,
						"appversion" : 						{
							"major" : 7,
							"minor" : 3,
							"revision" : 4,
							"architecture" : "x64",
							"modernui" : 1
						}
,
						"rect" : [ 100.0, 126.0, 703.0, 533.0 ],
						"bglocked" : 0,
						"openinpresentation" : 0,
						"default_fontsize" : 13.0,
						"default_fontface" : 0,
						"default_fontname" : "Arial",
						"gridonopen" : 1,
						"gridsize" : [ 5.0, 5.0 ],
						"gridsnaponopen" : 1,
						"objectsnaponopen" : 1,
						"statusbarvisible" : 2,
						"toolbarvisible" : 1,
						"lefttoolbarpinned" : 0,
						"toptoolbarpinned" : 0,
						"righttoolbarpinned" : 0,
						"bottomtoolbarpinned" : 0,
						"toolbars_unpinned_last_save" : 0,
						"tallnewobj" : 0,
						"boxanimatetime" : 200,
						"enablehscroll" : 1,
						"enablevscroll" : 1,
						"devicewidth" : 0.0,
						"description" : "",
						"digest" : "",
						"tags" : "",
						"style" : "",
						"subpatcher_template" : "",
						"showontab" : 1,
						"boxes" : [ 							{
								"box" : 								{
									"bgmode" : 0,
									"border" : 0,
									"clickthrough" : 0,
									"enablehscroll" : 0,
									"enablevscroll" : 0,
									"id" : "obj-7",
									"lockeddragscroll" : 0,
									"maxclass" : "bpatcher",
									"name" : "dada.commons.maxpat",
									"numinlets" : 0,
									"numoutlets" : 0,
									"offset" : [ 0.0, 0.0 ],
									"patching_rect" : [ 2.0, 4.0, 673.0, 516.0 ],
									"viewvisibility" : 1
								}

							}
 ],
						"lines" : [  ]
					}
,
					"patching_rect" : [ 142.0, 367.0, 73.0, 22.0 ],
					"saved_object_attributes" : 					{
						"description" : "",
						"digest" : "",
						"fontsize" : 13.0,
						"globalpatchername" : "",
						"style" : "",
						"tags" : ""
					}
,
					"style" : "",
					"text" : "p commons",
					"varname" : "basic_tab[8]"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"id" : "obj-11",
					"maxclass" : "newobj",
					"numinlets" : 0,
					"numoutlets" : 0,
					"patcher" : 					{
						"fileversion" : 1,
						"appversion" : 						{
							"major" : 7,
							"minor" : 3,
							"revision" : 4,
							"architecture" : "x64",
							"modernui" : 1
						}
,
						"rect" : [ 0.0, 26.0, 703.0, 533.0 ],
						"bglocked" : 0,
						"openinpresentation" : 0,
						"default_fontsize" : 13.0,
						"default_fontface" : 0,
						"default_fontname" : "Arial",
						"gridonopen" : 1,
						"gridsize" : [ 5.0, 5.0 ],
						"gridsnaponopen" : 1,
						"objectsnaponopen" : 1,
						"statusbarvisible" : 2,
						"toolbarvisible" : 1,
						"lefttoolbarpinned" : 0,
						"toptoolbarpinned" : 0,
						"righttoolbarpinned" : 0,
						"bottomtoolbarpinned" : 0,
						"toolbars_unpinned_last_save" : 0,
						"tallnewobj" : 0,
						"boxanimatetime" : 200,
						"enablehscroll" : 1,
						"enablevscroll" : 1,
						"devicewidth" : 0.0,
						"description" : "",
						"digest" : "",
						"tags" : "",
						"style" : "",
						"subpatcher_template" : "",
						"showontab" : 1,
						"boxes" : [ 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-31",
									"linecount" : 4,
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 253.5, 341.0, 448.0, 65.0 ],
									"style" : "",
									"text" : "The double \"score\" is tricky: the first one is to tell that we are setting the edge's score; the second one is because the content is itself a bach.score's gathered syntax; we might have used a \"score roll ...\" if the content was a bach.roll.",
									"textcolor" : [ 0.501961, 0.501961, 0.501961, 1.0 ]
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-27",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 18.0, 260.0, 43.0, 23.0 ],
									"style" : "",
									"text" : "dump"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-24",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 44.5, 498.0, 68.0, 23.0 ],
									"saved_object_attributes" : 									{
										"versionnumber" : 80001
									}
,
									"style" : "",
									"text" : "bach.print"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-18",
									"linecount" : 2,
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 253.5, 299.0, 390.0, 38.0 ],
									"style" : "",
									"text" : "meta edge 1 (label lowscore) ( score score (((( 4 4 ) (( 1/4 120 ))) ( 1 ( 4700. 100 0 )))))"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-16",
									"maxclass" : "newobj",
									"numinlets" : 3,
									"numoutlets" : 2,
									"outlettype" : [ "", "int" ],
									"patching_rect" : [ 458.75, 494.0, 104.0, 23.0 ],
									"style" : "",
									"text" : "bach.ezmidiplay"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-12",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 277.0, 456.0, 34.0, 23.0 ],
									"style" : "",
									"text" : "play"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-5",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 2,
									"outlettype" : [ "", "bang" ],
									"patching_rect" : [ 317.0, 410.0, 160.0, 23.0 ],
									"saved_object_attributes" : 									{
										"versionnumber" : 80001
									}
,
									"style" : "",
									"text" : "bach.keys score @keep 1"
								}

							}
, 							{
								"box" : 								{
									"bwcompatibility" : 70909,
									"constraintbeamsinspaces" : 0,
									"defaultnoteslots" : [ "null" ],
									"fontface" : 0,
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"id" : "obj-3",
									"loop" : [ "(", 1, 1, 0, ")", "(", 1, 2, 0, ")" ],
									"maxclass" : "bach.score",
									"numinlets" : 7,
									"numoutlets" : 9,
									"numvoices" : 1,
									"out" : "nnnnnnnn",
									"outlettype" : [ "", "", "", "", "", "", "", "", "bang" ],
									"patching_rect" : [ 317.0, 438.0, 181.0, 46.666664 ],
									"pitcheditrange" : [ "null" ],
									"stafflines" : [ 5 ],
									"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
									"versionnumber" : 80001,
									"voicenames" : [ "(", ")" ],
									"voicespacing" : [ -12.0, 17.6 ],
									"whole_score_data_0000000000" : [ "score", "(", "slotinfo", "(", 1, "(", "name", "velocity envelope", ")", "(", "type", "function", ")", "(", "key", 0, ")", "(", "range", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1080016896, ")", "(", "slope", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "representation", ")", "(", "grid", ")", "(", "ysnap", ")", "(", "domain", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, ")", "(", "domainslope", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "temporalmode", "relative", ")", "(", "extend", 0, ")", "(", "width", "duration", ")", "(", "height", "auto", ")", "(", "singleslotfortiednotes", 1, ")", "(", "copywhensplit", 0, ")", "(", "access", "readandwrite", ")", ")", "(", 2, "(", "name", "slot function", ")", "(", "type", "function", ")", "(", "key", 0, ")", "(", "range", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, ")", "(", "slope", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "representation", ")", "(", "grid", ")", "(", "ysnap", ")", "(", "domain", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, ")", "(", "domainslope", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "temporalmode", "relative", ")", "(", "extend", 0, ")", "(", "width", "duration", ")", "(", "height", "auto", ")", "(", "singleslotfortiednotes", 1, ")", "(", "copywhensplit", 0, ")", "(", "access", "readandwrite", ")", ")", "(", 3, "(", "name", "slot intlist", ")", "(", "type", "intlist", ")", "(", "key", 0, ")", "(", "range", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1080016896, ")", "(", "slope", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "representation", ")", "(", "default", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1078984704, ")", "(", "temporalmode", "none", ")", "(", "extend", 0, ")", "(", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", "(", "height", "auto", ")", "(", "singleslotfortiednotes", 1, ")", "(", "copywhensplit", 1, ")", "(", "access", "readandwrite", ")", ")", "(", 4, "(", "name", "slot floatlist", ")", "(", "type", "floatlist", ")", "(", "key", 0, ")", "(", "range", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, ")", "(", "slope", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "representation", ")", "(", "default", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "temporalmode", "none", ")", "(", "extend", 0, ")", "(", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", "(", "height", "auto", ")", "(", "singleslotfortiednotes", 1, ")", "(", "copywhensplit", 1, ")", "(", "access", "readandwrite", ")", ")", "(", 5, "(", "name", "slot int", ")", "(", "type", "int", ")", "(", "key", 0, ")", "(", "range", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1080016896, ")", "(", "slope", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "representation", ")", "(", "default", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1078984704, ")", "(", "temporalmode", "none", ")", "(", "extend", 0, ")", "(", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", "(", "height", "auto", ")", "(", "singleslotfortiednotes", 1, ")", "(", "copywhensplit", 1, ")", "(", "access", "readandwrite", ")", ")", "(", 6, "(", "name", "slot float", ")", "(", "type", "float", ")", "(", "key", 0, ")", "(", "range", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, ")", "(", "slope", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "representation", ")", "(", "default", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "temporalmode", "none", ")", "(", "extend", 0, ")", "(", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", "(", "height", "auto", ")", "(", "singleslotfortiednotes", 1, ")", "(", "copywhensplit", 1, ")", "(", "access", "readandwrite", ")", ")", "(", 7, "(", "name", "slot text", ")", "(", "type", "text", ")", "(", "key", 0, ")", "(", "temporalmode", "none", ")", "(", "extend", 0, ")", "(", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", "(", "height", "auto", ")", "(", "singleslotfortiednotes", 1, ")", "(", "copywhensplit", 0, ")", "(", "access", "readandwrite", ")", ")", "(", 8, "(", "name", "slot filelist", ")", "(", "type", "filelist", ")", "(", "key", 0, ")", "(", "temporalmode", "none", ")", "(", "extend", 0, ")", "(", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1080213504, ")", "(", "height", "auto", ")", "(", "singleslotfortiednotes", 1, ")", "(", "copywhensplit", 1, ")", "(", "access", "readandwrite", ")", ")", "(", 9, "(", "name", "slot spat", ")", "(", "type", "spat", ")", "(", "key", 0, ")", "(", "range", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1076101120, ")", "(", "slope", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "representation", ")", "(", "temporalmode", "relative", ")", "(", "extend", 0, ")", "(", "width", "duration", ")", "(", "height", "auto", ")", "(", "singleslotfortiednotes", 1, ")", "(", "copywhensplit", 0, ")", "(", "access", "readandwrite", ")", ")", "(", 10, "(", "name", "slot llll", ")", "(", "type", "llll", ")", "(", "key", 0, ")", "(", "temporalmode", "none", ")", "(", "extend", 0, ")", "(", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", "(", "height", "auto", ")", "(", "singleslotfortiednotes", 1, ")", "(", "copywhensplit", 0, ")", "(", "access", "readandwrite", ")", ")", "(", 11, "(", "name", "slot 11", ")", "(", "type", "none", ")", "(", "key", 0, ")", "(", "temporalmode", "none", ")", "(", "extend", 0, ")", "(", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", "(", "height", "auto", ")", "(", "singleslotfortiednotes", 1, ")", "(", "copywhensplit", 1, ")", "(", "access", "readandwrite", ")", ")", "(", 12, "(", "name", "slot 12", ")", "(", "type", "none", ")", "(", "key", 0, ")", "(", "temporalmode", "none", ")", "(", "extend", 0, ")", "(", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", "(", "height", "auto", ")", "(", "singleslotfortiednotes", 1, ")", "(", "copywhensplit", 1, ")", "(", "access", "readandwrite", ")", ")", "(", 13, "(", "name", "slot 13", ")", "(", "type", "none", ")", "(", "key", 0, ")", "(", "temporalmode", "none", ")", "(", "extend", 0, ")", "(", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", "(", "height", "auto", ")", "(", "singleslotfortiednotes", 1, ")", "(", "copywhensplit", 1, ")", "(", "access", "readandwrite", ")", ")", "(", 14, "(", "name", "slot 14", ")", "(", "type", "none", ")", "(", "key", 0, ")", "(", "temporalmode", "none", ")", "(", "extend", 0, ")", "(", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", "(", "height", "auto", ")", "(", "singleslotfortiednotes", 1, ")", "(", "copywhensplit", 1, ")", "(", "access", "readandwrite", ")", ")", "(", 15, "(", "name", "slot 15", ")", "(", "type", "none", ")", "(", "key", 0, ")", "(", "temporalmode", "none", ")", "(", "extend", 0, ")", "(", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", "(", "height", "auto", ")", "(", "singleslotfortiednotes", 1, ")", "(", "copywhensplit", 1, ")", "(", "access", "readandwrite", ")", ")", "(", 16, "(", "name", "slot 16", ")", "(", "type", "none", ")", "(", "key", 0, ")", "(", "temporalmode", "none", ")", "(", "extend", 0, ")", "(", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", "(", "height", "auto", ")", "(", "singleslotfortiednotes", 1, ")", "(", "copywhensplit", 1, ")", "(", "access", "readandwrite", ")", ")", "(", 17, "(", "name", "slot 17", ")", "(", "type", "none", ")", "(", "key", 0, ")", "(", "temporalmode", "none", ")", "(", "extend", 0, ")", "(", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", "(", "height", "auto", ")", "(", "singleslotfortiednotes", 1, ")", "(", "copywhensplit", 1, ")", "(", "access", "readandwrite", ")", ")", "(", 18, "(", "name", "slot 18", ")", "(", "type", "none", ")", "(", "key", 0, ")", "(", "temporalmode", "none", ")", "(", "extend", 0, ")", "(", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", "(", "height", "auto", ")", "(", "singleslotfortiednotes", 1, ")", "(", "copywhensplit", 1, ")", "(", "access", "readandwrite", ")", ")", "(", 19, "(", "name", "slot 19", ")", "(", "type", "none", ")", "(", "key", 0, ")", "(", "temporalmode", "none", ")", "(", "extend", 0, ")", "(", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", "(", "height", "auto", ")", "(", "singleslotfortiednotes", 1, ")", "(", "copywhensplit", 1, ")", "(", "access", "readandwrite", ")", ")", "(", 20, "(", "name", "dynamics", ")", "(", "type", "dynamics", ")", "(", "key", "d", ")", "(", "temporalmode", "none", ")", "(", "extend", 0, ")", "(", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079083008, ")", "(", "height", "auto", ")", "(", "singleslotfortiednotes", 1, ")", "(", "copywhensplit", 0, ")", "(", "access", "readandwrite", ")", ")", "(", 21, "(", "name", "lyrics", ")", "(", "type", "text", ")", "(", "key", "l", ")", "(", "temporalmode", "none", ")", "(", "extend", 0, ")", "(", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", "(", "height", "auto", ")", "(", "singleslotfortiednotes", 1, ")", "(", "copywhensplit", 0, ")", "(", "access", "readandwrite", ")", ")", "(", 22, "(", "name", "articulations", ")", "(", "type", "articulations", ")", "(", "key", "a", ")", "(", "temporalmode", "none", ")", "(", "extend", 0, ")", "(", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079738368, ")", "(", "height", "auto", ")", "(", "singleslotfortiednotes", 1, ")", "(", "copywhensplit", 1, ")", "(", "access", "readandwrite", ")", ")", "(", 23, "(", "name", "notehead", ")", "(", "type", "notehead", ")", "(", "key", "h", ")", "(", "temporalmode", "none", ")", "(", "extend", 0, ")", "(", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079738368, ")", "(", "height", "auto", ")", "(", "singleslotfortiednotes", 1, ")", "(", "copywhensplit", 1, ")", "(", "access", "readandwrite", ")", ")", "(", 24, "(", "name", "slot 24", ")", "(", "type", "none", ")", "(", "key", 0, ")", "(", "temporalmode", "none", ")", "(", "extend", 0, ")", "(", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", "(", "height", "auto", ")", "(", "singleslotfortiednotes", 1, ")", "(", "copywhensplit", 1, ")", "(", "access", "readandwrite", ")", ")", "(", 25, "(", "name", "slot 25", ")", "(", "type", "none", ")", "(", "key", 0, ")", "(", "temporalmode", "none", ")", "(", "extend", 0, ")", "(", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", "(", "height", "auto", ")", "(", "singleslotfortiednotes", 1, ")", "(", "copywhensplit", 1, ")", "(", "access", "readandwrite", ")", ")", "(", 26, "(", "name", "slot 26", ")", "(", "type", "none", ")", "(", "key", 0, ")", "(", "temporalmode", "none", ")", "(", "extend", 0, ")", "(", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", "(", "height", "auto", ")", "(", "singleslotfortiednotes", 1, ")", "(", "copywhensplit", 1, ")", "(", "access", "readandwrite", ")", ")", "(", 27, "(", "name", "slot 27", ")", "(", "type", "none", ")", "(", "key", 0, ")", "(", "temporalmode", "none", ")", "(", "extend", 0, ")", "(", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", "(", "height", "auto", ")", "(", "singleslotfortiednotes", 1, ")", "(", "copywhensplit", 1, ")", "(", "access", "readandwrite", ")", ")", "(", 28, "(", "name", "slot 28", ")", "(", "type", "none", ")", "(", "key", 0, ")", "(", "temporalmode", "none", ")", "(", "extend", 0, ")", "(", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", "(", "height", "auto", ")", "(", "singleslotfortiednotes", 1, ")", "(", "copywhensplit", 1, ")", "(", "access", "readandwrite", ")", ")", "(", 29, "(", "name", "slot 29", ")", "(", "type", "none", ")", "(", "key", 0, ")", "(", "temporalmode", "none", ")", "(", "extend", 0, ")", "(", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", "(", "height", "auto", ")", "(", "singleslotfortiednotes", 1, ")", "(", "copywhensplit", 1, ")", "(", "access", "readandwrite", ")", ")", "(", 30, "(", "name", "slot 30", ")", "(", "type", "none", ")", "(", "key", 0, ")", "(", "temporalmode", "none", ")", "(", "extend", 0, ")", "(", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", "(", "height", "auto", ")", "(", "singleslotfortiednotes", 1, ")", "(", "copywhensplit", 1, ")", "(", "access", "readandwrite", ")", ")", ")", "(", "commands", "(", 1, "(", "note", "note", ")", "(", "chord", "chord", ")", "(", "rest", "rest", ")", "(", "key", 0, ")", ")", "(", 2, "(", "note", "note", ")", "(", "chord", "chord", ")", "(", "rest", "rest", ")", "(", "key", 0, ")", ")", "(", 3, "(", "note", "note", ")", "(", "chord", "chord", ")", "(", "rest", "rest", ")", "(", "key", 0, ")", ")", "(", 4, "(", "note", "note", ")", "(", "chord", "chord", ")", "(", "rest", "rest", ")", "(", "key", 0, ")", ")", "(", 5, "(", "note", "note", ")", "(", "chord", "chord", ")", "(", "rest", "rest", ")", "(", "key", 0, ")", ")", ")", "(", "markers", ")", "(", "midichannels", 1, ")", "(", "articulationinfo", ")", "(", "noteheadinfo", ")", "(", "(", "(", "(", 4, 4, ")", "(", "(", "1/4", 120, ")", ")", ")", "(", "leveltype", 1, ")", "(", "(", "leveltype", 8, ")", "(", "1/8", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1086096384, 100, 0, 0, ")", 0, ")", "(", "1/8", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1086096384, 100, 0, 0, ")", 0, ")", ")", "(", "(", "leveltype", 8, ")", "(", "1/8", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1086096384, 100, 0, 0, ")", 0, ")", "(", "1/8", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1086096384, 100, 0, 0, ")", 0, ")", ")", "(", "(", "leveltype", 8, ")", "(", "1/8", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1086096384, 100, 0, 0, ")", 0, ")", "(", "1/8", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1086096384, 100, 0, 0, ")", 0, ")", ")", "(", "(", "leveltype", 8, ")", "(", "1/8", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1086096384, 100, 0, 0, ")", 0, ")", "(", "1/8", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1086096384, 100, 0, 0, ")", 0, ")", ")", 0, ")", 0, ")" ],
									"whole_score_data_count" : [ 1 ]
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-26",
									"linecount" : 2,
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 10.0, 66.567627, 672.0, 36.0 ],
									"style" : "",
									"text" : "When edges have metadata, the metadata type can also be a complex roll/score, instead of pitch/velocity couples.\nHere's an example on how to achieve that. Scores contained within the object are saved with the patch",
									"textcolor" : [ 0.501961, 0.501961, 0.501961, 1.0 ]
								}

							}
, 							{
								"box" : 								{
									"bubble" : 1,
									"id" : "obj-17",
									"linecount" : 2,
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 443.0, 117.5, 150.0, 40.0 ],
									"style" : "",
									"text" : "Assign one score to each vertex"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-15",
									"maxclass" : "newobj",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 300.0, 264.0, 132.0, 23.0 ],
									"style" : "",
									"text" : "bach.prepend scores"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-14",
									"maxclass" : "newobj",
									"numinlets" : 3,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 300.0, 231.0, 139.0, 23.0 ],
									"saved_object_attributes" : 									{
										"versionnumber" : 80001
									}
,
									"style" : "",
									"text" : "bach.join 3 @inwrap 1"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-13",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 360.0, 126.0, 75.0, 23.0 ],
									"style" : "",
									"text" : "dump body"
								}

							}
, 							{
								"box" : 								{
									"bwcompatibility" : 70909,
									"constraintbeamsinspaces" : 0,
									"defaultnoteslots" : [ "null" ],
									"fontface" : 0,
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"id" : "obj-11",
									"loop" : [ "(", 1, 1, 0, ")", "(", 1, 2, 0, ")" ],
									"maxclass" : "bach.score",
									"numinlets" : 7,
									"numoutlets" : 9,
									"numvoices" : 1,
									"out" : "nnnnnnnn",
									"outlettype" : [ "", "", "", "", "", "", "", "", "bang" ],
									"patching_rect" : [ 498.0, 167.0, 133.0, 46.666664 ],
									"pitcheditrange" : [ "null" ],
									"stafflines" : [ 5 ],
									"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
									"versionnumber" : 80001,
									"voicenames" : [ "(", ")" ],
									"voicespacing" : [ -12.0, 17.6 ],
									"whole_score_data_0000000000" : [ "score", "(", "slotinfo", "(", 1, "(", "name", "velocity envelope", ")", "(", "type", "function", ")", "(", "key", 0, ")", "(", "range", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1080016896, ")", "(", "slope", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "representation", ")", "(", "grid", ")", "(", "ysnap", ")", "(", "domain", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, ")", "(", "domainslope", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "temporalmode", "relative", ")", "(", "extend", 0, ")", "(", "width", "duration", ")", "(", "height", "auto", ")", "(", "singleslotfortiednotes", 1, ")", "(", "copywhensplit", 0, ")", "(", "access", "readandwrite", ")", ")", "(", 2, "(", "name", "slot function", ")", "(", "type", "function", ")", "(", "key", 0, ")", "(", "range", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, ")", "(", "slope", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "representation", ")", "(", "grid", ")", "(", "ysnap", ")", "(", "domain", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, ")", "(", "domainslope", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "temporalmode", "relative", ")", "(", "extend", 0, ")", "(", "width", "duration", ")", "(", "height", "auto", ")", "(", "singleslotfortiednotes", 1, ")", "(", "copywhensplit", 0, ")", "(", "access", "readandwrite", ")", ")", "(", 3, "(", "name", "slot intlist", ")", "(", "type", "intlist", ")", "(", "key", 0, ")", "(", "range", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1080016896, ")", "(", "slope", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "representation", ")", "(", "default", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1078984704, ")", "(", "temporalmode", "none", ")", "(", "extend", 0, ")", "(", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", "(", "height", "auto", ")", "(", "singleslotfortiednotes", 1, ")", "(", "copywhensplit", 1, ")", "(", "access", "readandwrite", ")", ")", "(", 4, "(", "name", "slot floatlist", ")", "(", "type", "floatlist", ")", "(", "key", 0, ")", "(", "range", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, ")", "(", "slope", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "representation", ")", "(", "default", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "temporalmode", "none", ")", "(", "extend", 0, ")", "(", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", "(", "height", "auto", ")", "(", "singleslotfortiednotes", 1, ")", "(", "copywhensplit", 1, ")", "(", "access", "readandwrite", ")", ")", "(", 5, "(", "name", "slot int", ")", "(", "type", "int", ")", "(", "key", 0, ")", "(", "range", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1080016896, ")", "(", "slope", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "representation", ")", "(", "default", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1078984704, ")", "(", "temporalmode", "none", ")", "(", "extend", 0, ")", "(", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", "(", "height", "auto", ")", "(", "singleslotfortiednotes", 1, ")", "(", "copywhensplit", 1, ")", "(", "access", "readandwrite", ")", ")", "(", 6, "(", "name", "slot float", ")", "(", "type", "float", ")", "(", "key", 0, ")", "(", "range", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, ")", "(", "slope", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "representation", ")", "(", "default", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "temporalmode", "none", ")", "(", "extend", 0, ")", "(", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", "(", "height", "auto", ")", "(", "singleslotfortiednotes", 1, ")", "(", "copywhensplit", 1, ")", "(", "access", "readandwrite", ")", ")", "(", 7, "(", "name", "slot text", ")", "(", "type", "text", ")", "(", "key", 0, ")", "(", "temporalmode", "none", ")", "(", "extend", 0, ")", "(", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", "(", "height", "auto", ")", "(", "singleslotfortiednotes", 1, ")", "(", "copywhensplit", 0, ")", "(", "access", "readandwrite", ")", ")", "(", 8, "(", "name", "slot filelist", ")", "(", "type", "filelist", ")", "(", "key", 0, ")", "(", "temporalmode", "none", ")", "(", "extend", 0, ")", "(", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1080213504, ")", "(", "height", "auto", ")", "(", "singleslotfortiednotes", 1, ")", "(", "copywhensplit", 1, ")", "(", "access", "readandwrite", ")", ")", "(", 9, "(", "name", "slot spat", ")", "(", "type", "spat", ")", "(", "key", 0, ")", "(", "range", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1076101120, ")", "(", "slope", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "representation", ")", "(", "temporalmode", "relative", ")", "(", "extend", 0, ")", "(", "width", "duration", ")", "(", "height", "auto", ")", "(", "singleslotfortiednotes", 1, ")", "(", "copywhensplit", 0, ")", "(", "access", "readandwrite", ")", ")", "(", 10, "(", "name", "slot llll", ")", "(", "type", "llll", ")", "(", "key", 0, ")", "(", "temporalmode", "none", ")", "(", "extend", 0, ")", "(", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", "(", "height", "auto", ")", "(", "singleslotfortiednotes", 1, ")", "(", "copywhensplit", 0, ")", "(", "access", "readandwrite", ")", ")", "(", 11, "(", "name", "slot 11", ")", "(", "type", "none", ")", "(", "key", 0, ")", "(", "temporalmode", "none", ")", "(", "extend", 0, ")", "(", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", "(", "height", "auto", ")", "(", "singleslotfortiednotes", 1, ")", "(", "copywhensplit", 1, ")", "(", "access", "readandwrite", ")", ")", "(", 12, "(", "name", "slot 12", ")", "(", "type", "none", ")", "(", "key", 0, ")", "(", "temporalmode", "none", ")", "(", "extend", 0, ")", "(", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", "(", "height", "auto", ")", "(", "singleslotfortiednotes", 1, ")", "(", "copywhensplit", 1, ")", "(", "access", "readandwrite", ")", ")", "(", 13, "(", "name", "slot 13", ")", "(", "type", "none", ")", "(", "key", 0, ")", "(", "temporalmode", "none", ")", "(", "extend", 0, ")", "(", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", "(", "height", "auto", ")", "(", "singleslotfortiednotes", 1, ")", "(", "copywhensplit", 1, ")", "(", "access", "readandwrite", ")", ")", "(", 14, "(", "name", "slot 14", ")", "(", "type", "none", ")", "(", "key", 0, ")", "(", "temporalmode", "none", ")", "(", "extend", 0, ")", "(", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", "(", "height", "auto", ")", "(", "singleslotfortiednotes", 1, ")", "(", "copywhensplit", 1, ")", "(", "access", "readandwrite", ")", ")", "(", 15, "(", "name", "slot 15", ")", "(", "type", "none", ")", "(", "key", 0, ")", "(", "temporalmode", "none", ")", "(", "extend", 0, ")", "(", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", "(", "height", "auto", ")", "(", "singleslotfortiednotes", 1, ")", "(", "copywhensplit", 1, ")", "(", "access", "readandwrite", ")", ")", "(", 16, "(", "name", "slot 16", ")", "(", "type", "none", ")", "(", "key", 0, ")", "(", "temporalmode", "none", ")", "(", "extend", 0, ")", "(", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", "(", "height", "auto", ")", "(", "singleslotfortiednotes", 1, ")", "(", "copywhensplit", 1, ")", "(", "access", "readandwrite", ")", ")", "(", 17, "(", "name", "slot 17", ")", "(", "type", "none", ")", "(", "key", 0, ")", "(", "temporalmode", "none", ")", "(", "extend", 0, ")", "(", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", "(", "height", "auto", ")", "(", "singleslotfortiednotes", 1, ")", "(", "copywhensplit", 1, ")", "(", "access", "readandwrite", ")", ")", "(", 18, "(", "name", "slot 18", ")", "(", "type", "none", ")", "(", "key", 0, ")", "(", "temporalmode", "none", ")", "(", "extend", 0, ")", "(", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", "(", "height", "auto", ")", "(", "singleslotfortiednotes", 1, ")", "(", "copywhensplit", 1, ")", "(", "access", "readandwrite", ")", ")", "(", 19, "(", "name", "slot 19", ")", "(", "type", "none", ")", "(", "key", 0, ")", "(", "temporalmode", "none", ")", "(", "extend", 0, ")", "(", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", "(", "height", "auto", ")", "(", "singleslotfortiednotes", 1, ")", "(", "copywhensplit", 1, ")", "(", "access", "readandwrite", ")", ")", "(", 20, "(", "name", "dynamics", ")", "(", "type", "dynamics", ")", "(", "key", "d", ")", "(", "temporalmode", "none", ")", "(", "extend", 0, ")", "(", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079083008, ")", "(", "height", "auto", ")", "(", "singleslotfortiednotes", 1, ")", "(", "copywhensplit", 0, ")", "(", "access", "readandwrite", ")", ")", "(", 21, "(", "name", "lyrics", ")", "(", "type", "text", ")", "(", "key", "l", ")", "(", "temporalmode", "none", ")", "(", "extend", 0, ")", "(", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", "(", "height", "auto", ")", "(", "singleslotfortiednotes", 1, ")", "(", "copywhensplit", 0, ")", "(", "access", "readandwrite", ")", ")", "(", 22, "(", "name", "articulations", ")", "(", "type", "articulations", ")", "(", "key", "a", ")", "(", "temporalmode", "none", ")", "(", "extend", 0, ")", "(", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079738368, ")", "(", "height", "auto", ")", "(", "singleslotfortiednotes", 1, ")", "(", "copywhensplit", 1, ")", "(", "access", "readandwrite", ")", ")", "(", 23, "(", "name", "notehead", ")", "(", "type", "notehead", ")", "(", "key", "h", ")", "(", "temporalmode", "none", ")", "(", "extend", 0, ")", "(", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079738368, ")", "(", "height", "auto", ")", "(", "singleslotfortiednotes", 1, ")", "(", "copywhensplit", 1, ")", "(", "access", "readandwrite", ")", ")", "(", 24, "(", "name", "slot 24", ")", "(", "type", "none", ")", "(", "key", 0, ")", "(", "temporalmode", "none", ")", "(", "extend", 0, ")", "(", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", "(", "height", "auto", ")", "(", "singleslotfortiednotes", 1, ")", "(", "copywhensplit", 1, ")", "(", "access", "readandwrite", ")", ")", "(", 25, "(", "name", "slot 25", ")", "(", "type", "none", ")", "(", "key", 0, ")", "(", "temporalmode", "none", ")", "(", "extend", 0, ")", "(", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", "(", "height", "auto", ")", "(", "singleslotfortiednotes", 1, ")", "(", "copywhensplit", 1, ")", "(", "access", "readandwrite", ")", ")", "(", 26, "(", "name", "slot 26", ")", "(", "type", "none", ")", "(", "key", 0, ")", "(", "temporalmode", "none", ")", "(", "extend", 0, ")", "(", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", "(", "height", "auto", ")", "(", "singleslotfortiednotes", 1, ")", "(", "copywhensplit", 1, ")", "(", "access", "readandwrite", ")", ")", "(", 27, "(", "name", "slot 27", ")", "(", "type", "none", ")", "(", "key", 0, ")", "(", "temporalmode", "none", ")", "(", "extend", 0, ")", "(", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", "(", "height", "auto", ")", "(", "singleslotfortiednotes", 1, ")", "(", "copywhensplit", 1, ")", "(", "access", "readandwrite", ")", ")", "(", 28, "(", "name", "slot 28", ")", "(", "type", "none", ")", "(", "key", 0, ")", "(", "temporalmode", "none", ")", "(", "extend", 0, ")", "(", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", "(", "height", "auto", ")", "(", "singleslotfortiednotes", 1, ")", "(", "copywhensplit", 1, ")", "(", "access", "readandwrite", ")", ")", "(", 29, "(", "name", "slot 29", ")", "(", "type", "none", ")", "(", "key", 0, ")", "(", "temporalmode", "none", ")", "(", "extend", 0, ")", "(", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", "(", "height", "auto", ")", "(", "singleslotfortiednotes", 1, ")", "(", "copywhensplit", 1, ")", "(", "access", "readandwrite", ")", ")", "(", 30, "(", "name", "slot 30", ")", "(", "type", "none", ")", "(", "key", 0, ")", "(", "temporalmode", "none", ")", "(", "extend", 0, ")", "(", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", "(", "height", "auto", ")", "(", "singleslotfortiednotes", 1, ")", "(", "copywhensplit", 1, ")", "(", "access", "readandwrite", ")", ")", ")", "(", "commands", "(", 1, "(", "note", "note", ")", "(", "chord", "chord", ")", "(", "rest", "rest", ")", "(", "key", 0, ")", ")", "(", 2, "(", "note", "note", ")", "(", "chord", "chord", ")", "(", "rest", "rest", ")", "(", "key", 0, ")", ")", "(", 3, "(", "note", "note", ")", "(", "chord", "chord", ")", "(", "rest", "rest", ")", "(", "key", 0, ")", ")", "(", 4, "(", "note", "note", ")", "(", "chord", "chord", ")", "(", "rest", "rest", ")", "(", "key", 0, ")", ")", "(", 5, "(", "note", "note", ")", "(", "chord", "chord", ")", "(", "rest", "rest", ")", "(", "key", 0, ")", ")", ")", "(", "markers", ")", "(", "midichannels", 1, ")", "(", "articulationinfo", ")", "(", "noteheadinfo", ")", "(", "(", "(", "(", 4, 4, ")", "(", "(", "1/4", 120, ")", ")", ")", "(", "leveltype", 1, ")", "(", "(", "leveltype", 8, ")", "(", "1/8", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1086096384, 100, 0, 0, ")", 0, ")", "(", "1/8", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1086096384, 100, 0, 0, ")", 0, ")", ")", "(", "(", "leveltype", 8, ")", "(", "1/8", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1086096384, 100, 0, 0, ")", 0, ")", "(", "1/8", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1086096384, 100, 0, 0, ")", 0, ")", ")", "(", "(", "leveltype", 8, ")", "(", "1/8", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1086096384, 100, 0, 0, ")", 0, ")", "(", "1/8", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1086096384, 100, 0, 0, ")", 0, ")", ")", "(", "(", "leveltype", 8, ")", "(", "1/8", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1086096384, 100, 0, 0, ")", 0, ")", "(", "1/8", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1086096384, 100, 0, 0, ")", 0, ")", ")", 0, ")", 0, ")" ],
									"whole_score_data_count" : [ 1 ]
								}

							}
, 							{
								"box" : 								{
									"bwcompatibility" : 70909,
									"constraintbeamsinspaces" : 0,
									"defaultnoteslots" : [ "null" ],
									"fontface" : 0,
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"id" : "obj-10",
									"loop" : [ "(", 1, 1, 0, ")", "(", 1, 2, 0, ")" ],
									"maxclass" : "bach.score",
									"numinlets" : 7,
									"numoutlets" : 9,
									"numvoices" : 1,
									"out" : "nnnnnnnn",
									"outlettype" : [ "", "", "", "", "", "", "", "", "bang" ],
									"patching_rect" : [ 360.0, 167.0, 124.0, 46.666664 ],
									"pitcheditrange" : [ "null" ],
									"stafflines" : [ 5 ],
									"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
									"versionnumber" : 80001,
									"voicenames" : [ "(", ")" ],
									"voicespacing" : [ -12.0, 17.6 ],
									"whole_score_data_0000000000" : [ "score", "(", "slotinfo", "(", 1, "(", "name", "velocity envelope", ")", "(", "type", "function", ")", "(", "key", 0, ")", "(", "range", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1080016896, ")", "(", "slope", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "representation", ")", "(", "grid", ")", "(", "ysnap", ")", "(", "domain", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, ")", "(", "domainslope", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "temporalmode", "relative", ")", "(", "extend", 0, ")", "(", "width", "duration", ")", "(", "height", "auto", ")", "(", "singleslotfortiednotes", 1, ")", "(", "copywhensplit", 0, ")", "(", "access", "readandwrite", ")", ")", "(", 2, "(", "name", "slot function", ")", "(", "type", "function", ")", "(", "key", 0, ")", "(", "range", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, ")", "(", "slope", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "representation", ")", "(", "grid", ")", "(", "ysnap", ")", "(", "domain", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, ")", "(", "domainslope", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "temporalmode", "relative", ")", "(", "extend", 0, ")", "(", "width", "duration", ")", "(", "height", "auto", ")", "(", "singleslotfortiednotes", 1, ")", "(", "copywhensplit", 0, ")", "(", "access", "readandwrite", ")", ")", "(", 3, "(", "name", "slot intlist", ")", "(", "type", "intlist", ")", "(", "key", 0, ")", "(", "range", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1080016896, ")", "(", "slope", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "representation", ")", "(", "default", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1078984704, ")", "(", "temporalmode", "none", ")", "(", "extend", 0, ")", "(", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", "(", "height", "auto", ")", "(", "singleslotfortiednotes", 1, ")", "(", "copywhensplit", 1, ")", "(", "access", "readandwrite", ")", ")", "(", 4, "(", "name", "slot floatlist", ")", "(", "type", "floatlist", ")", "(", "key", 0, ")", "(", "range", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, ")", "(", "slope", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "representation", ")", "(", "default", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "temporalmode", "none", ")", "(", "extend", 0, ")", "(", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", "(", "height", "auto", ")", "(", "singleslotfortiednotes", 1, ")", "(", "copywhensplit", 1, ")", "(", "access", "readandwrite", ")", ")", "(", 5, "(", "name", "slot int", ")", "(", "type", "int", ")", "(", "key", 0, ")", "(", "range", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1080016896, ")", "(", "slope", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "representation", ")", "(", "default", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1078984704, ")", "(", "temporalmode", "none", ")", "(", "extend", 0, ")", "(", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", "(", "height", "auto", ")", "(", "singleslotfortiednotes", 1, ")", "(", "copywhensplit", 1, ")", "(", "access", "readandwrite", ")", ")", "(", 6, "(", "name", "slot float", ")", "(", "type", "float", ")", "(", "key", 0, ")", "(", "range", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, ")", "(", "slope", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "representation", ")", "(", "default", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "temporalmode", "none", ")", "(", "extend", 0, ")", "(", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", "(", "height", "auto", ")", "(", "singleslotfortiednotes", 1, ")", "(", "copywhensplit", 1, ")", "(", "access", "readandwrite", ")", ")", "(", 7, "(", "name", "slot text", ")", "(", "type", "text", ")", "(", "key", 0, ")", "(", "temporalmode", "none", ")", "(", "extend", 0, ")", "(", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", "(", "height", "auto", ")", "(", "singleslotfortiednotes", 1, ")", "(", "copywhensplit", 0, ")", "(", "access", "readandwrite", ")", ")", "(", 8, "(", "name", "slot filelist", ")", "(", "type", "filelist", ")", "(", "key", 0, ")", "(", "temporalmode", "none", ")", "(", "extend", 0, ")", "(", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1080213504, ")", "(", "height", "auto", ")", "(", "singleslotfortiednotes", 1, ")", "(", "copywhensplit", 1, ")", "(", "access", "readandwrite", ")", ")", "(", 9, "(", "name", "slot spat", ")", "(", "type", "spat", ")", "(", "key", 0, ")", "(", "range", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1076101120, ")", "(", "slope", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "representation", ")", "(", "temporalmode", "relative", ")", "(", "extend", 0, ")", "(", "width", "duration", ")", "(", "height", "auto", ")", "(", "singleslotfortiednotes", 1, ")", "(", "copywhensplit", 0, ")", "(", "access", "readandwrite", ")", ")", "(", 10, "(", "name", "slot llll", ")", "(", "type", "llll", ")", "(", "key", 0, ")", "(", "temporalmode", "none", ")", "(", "extend", 0, ")", "(", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", "(", "height", "auto", ")", "(", "singleslotfortiednotes", 1, ")", "(", "copywhensplit", 0, ")", "(", "access", "readandwrite", ")", ")", "(", 11, "(", "name", "slot 11", ")", "(", "type", "none", ")", "(", "key", 0, ")", "(", "temporalmode", "none", ")", "(", "extend", 0, ")", "(", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", "(", "height", "auto", ")", "(", "singleslotfortiednotes", 1, ")", "(", "copywhensplit", 1, ")", "(", "access", "readandwrite", ")", ")", "(", 12, "(", "name", "slot 12", ")", "(", "type", "none", ")", "(", "key", 0, ")", "(", "temporalmode", "none", ")", "(", "extend", 0, ")", "(", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", "(", "height", "auto", ")", "(", "singleslotfortiednotes", 1, ")", "(", "copywhensplit", 1, ")", "(", "access", "readandwrite", ")", ")", "(", 13, "(", "name", "slot 13", ")", "(", "type", "none", ")", "(", "key", 0, ")", "(", "temporalmode", "none", ")", "(", "extend", 0, ")", "(", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", "(", "height", "auto", ")", "(", "singleslotfortiednotes", 1, ")", "(", "copywhensplit", 1, ")", "(", "access", "readandwrite", ")", ")", "(", 14, "(", "name", "slot 14", ")", "(", "type", "none", ")", "(", "key", 0, ")", "(", "temporalmode", "none", ")", "(", "extend", 0, ")", "(", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", "(", "height", "auto", ")", "(", "singleslotfortiednotes", 1, ")", "(", "copywhensplit", 1, ")", "(", "access", "readandwrite", ")", ")", "(", 15, "(", "name", "slot 15", ")", "(", "type", "none", ")", "(", "key", 0, ")", "(", "temporalmode", "none", ")", "(", "extend", 0, ")", "(", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", "(", "height", "auto", ")", "(", "singleslotfortiednotes", 1, ")", "(", "copywhensplit", 1, ")", "(", "access", "readandwrite", ")", ")", "(", 16, "(", "name", "slot 16", ")", "(", "type", "none", ")", "(", "key", 0, ")", "(", "temporalmode", "none", ")", "(", "extend", 0, ")", "(", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", "(", "height", "auto", ")", "(", "singleslotfortiednotes", 1, ")", "(", "copywhensplit", 1, ")", "(", "access", "readandwrite", ")", ")", "(", 17, "(", "name", "slot 17", ")", "(", "type", "none", ")", "(", "key", 0, ")", "(", "temporalmode", "none", ")", "(", "extend", 0, ")", "(", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", "(", "height", "auto", ")", "(", "singleslotfortiednotes", 1, ")", "(", "copywhensplit", 1, ")", "(", "access", "readandwrite", ")", ")", "(", 18, "(", "name", "slot 18", ")", "(", "type", "none", ")", "(", "key", 0, ")", "(", "temporalmode", "none", ")", "(", "extend", 0, ")", "(", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", "(", "height", "auto", ")", "(", "singleslotfortiednotes", 1, ")", "(", "copywhensplit", 1, ")", "(", "access", "readandwrite", ")", ")", "(", 19, "(", "name", "slot 19", ")", "(", "type", "none", ")", "(", "key", 0, ")", "(", "temporalmode", "none", ")", "(", "extend", 0, ")", "(", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", "(", "height", "auto", ")", "(", "singleslotfortiednotes", 1, ")", "(", "copywhensplit", 1, ")", "(", "access", "readandwrite", ")", ")", "(", 20, "(", "name", "dynamics", ")", "(", "type", "dynamics", ")", "(", "key", "d", ")", "(", "temporalmode", "none", ")", "(", "extend", 0, ")", "(", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079083008, ")", "(", "height", "auto", ")", "(", "singleslotfortiednotes", 1, ")", "(", "copywhensplit", 0, ")", "(", "access", "readandwrite", ")", ")", "(", 21, "(", "name", "lyrics", ")", "(", "type", "text", ")", "(", "key", "l", ")", "(", "temporalmode", "none", ")", "(", "extend", 0, ")", "(", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", "(", "height", "auto", ")", "(", "singleslotfortiednotes", 1, ")", "(", "copywhensplit", 0, ")", "(", "access", "readandwrite", ")", ")", "(", 22, "(", "name", "articulations", ")", "(", "type", "articulations", ")", "(", "key", "a", ")", "(", "temporalmode", "none", ")", "(", "extend", 0, ")", "(", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079738368, ")", "(", "height", "auto", ")", "(", "singleslotfortiednotes", 1, ")", "(", "copywhensplit", 1, ")", "(", "access", "readandwrite", ")", ")", "(", 23, "(", "name", "notehead", ")", "(", "type", "notehead", ")", "(", "key", "h", ")", "(", "temporalmode", "none", ")", "(", "extend", 0, ")", "(", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079738368, ")", "(", "height", "auto", ")", "(", "singleslotfortiednotes", 1, ")", "(", "copywhensplit", 1, ")", "(", "access", "readandwrite", ")", ")", "(", 24, "(", "name", "slot 24", ")", "(", "type", "none", ")", "(", "key", 0, ")", "(", "temporalmode", "none", ")", "(", "extend", 0, ")", "(", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", "(", "height", "auto", ")", "(", "singleslotfortiednotes", 1, ")", "(", "copywhensplit", 1, ")", "(", "access", "readandwrite", ")", ")", "(", 25, "(", "name", "slot 25", ")", "(", "type", "none", ")", "(", "key", 0, ")", "(", "temporalmode", "none", ")", "(", "extend", 0, ")", "(", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", "(", "height", "auto", ")", "(", "singleslotfortiednotes", 1, ")", "(", "copywhensplit", 1, ")", "(", "access", "readandwrite", ")", ")", "(", 26, "(", "name", "slot 26", ")", "(", "type", "none", ")", "(", "key", 0, ")", "(", "temporalmode", "none", ")", "(", "extend", 0, ")", "(", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", "(", "height", "auto", ")", "(", "singleslotfortiednotes", 1, ")", "(", "copywhensplit", 1, ")", "(", "access", "readandwrite", ")", ")", "(", 27, "(", "name", "slot 27", ")", "(", "type", "none", ")", "(", "key", 0, ")", "(", "temporalmode", "none", ")", "(", "extend", 0, ")", "(", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", "(", "height", "auto", ")", "(", "singleslotfortiednotes", 1, ")", "(", "copywhensplit", 1, ")", "(", "access", "readandwrite", ")", ")", "(", 28, "(", "name", "slot 28", ")", "(", "type", "none", ")", "(", "key", 0, ")", "(", "temporalmode", "none", ")", "(", "extend", 0, ")", "(", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", "(", "height", "auto", ")", "(", "singleslotfortiednotes", 1, ")", "(", "copywhensplit", 1, ")", "(", "access", "readandwrite", ")", ")", "(", 29, "(", "name", "slot 29", ")", "(", "type", "none", ")", "(", "key", 0, ")", "(", "temporalmode", "none", ")", "(", "extend", 0, ")", "(", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", "(", "height", "auto", ")", "(", "singleslotfortiednotes", 1, ")", "(", "copywhensplit", 1, ")", "(", "access", "readandwrite", ")", ")", "(", 30, "(", "name", "slot 30", ")", "(", "type", "none", ")", "(", "key", 0, ")", "(", "temporalmode", "none", ")", "(", "extend", 0, ")", "(", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", "(", "height", "auto", ")", "(", "singleslotfortiednotes", 1, ")", "(", "copywhensplit", 1, ")", "(", "access", "readandwrite", ")", ")", ")", "(", "commands", "(", 1, "(", "note", "note", ")", "(", "chord", "chord", ")", "(", "rest", "rest", ")", "(", "key", 0, ")", ")", "(", 2, "(", "note", "note", ")", "(", "chord", "chord", ")", "(", "rest", "rest", ")", "(", "key", 0, ")", ")", "(", 3, "(", "note", "note", ")", "(", "chord", "chord", ")", "(", "rest", "rest", ")", "(", "key", 0, ")", ")", "(", 4, "(", "note", "note", ")", "(", "chord", "chord", ")", "(", "rest", "rest", ")", "(", "key", 0, ")", ")", "(", 5, "(", "note", "note", ")", "(", "chord", "chord", ")", "(", "rest", "rest", ")", "(", "key", 0, ")", ")", ")", "(", "markers", ")", "(", "midichannels", 1, ")", "(", "articulationinfo", ")", "(", "noteheadinfo", ")", "(", "(", "(", "(", 4, 4, ")", "(", "(", "1/4", 130, ")", ")", ")", "(", "leveltype", 1, ")", "(", "(", "leveltype", 8, ")", "(", "-1/16", 0, ")", "(", "(", "leveltype", 1, ")", "(", "1/16", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1086045184, 100, 0, 0, ")", 0, ")", "(", "1/16", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1086173184, 100, 0, 0, ")", 0, ")", "(", "1/16", "(", "G#6", 100, 0, 0, ")", 0, ")", ")", ")", "(", "(", "leveltype", 8, ")", "(", "1/8", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1086338560, 100, 0, 0, ")", 0, ")", "(", "(", "leveltype", 1, ")", "(", "1/16", "(", "G#6", 100, 0, 0, ")", 0, ")", "(", "1/16", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1086338560, 100, 0, 0, ")", 0, ")", ")", ")", "(", "-1/2", 0, ")", 0, ")", 0, ")" ],
									"whole_score_data_count" : [ 1 ]
								}

							}
, 							{
								"box" : 								{
									"bwcompatibility" : 70909,
									"constraintbeamsinspaces" : 0,
									"defaultnoteslots" : [ "null" ],
									"fontface" : 0,
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"id" : "obj-9",
									"loop" : [ "(", 1, 1, 0, ")", "(", 1, 2, 0, ")" ],
									"maxclass" : "bach.score",
									"numinlets" : 7,
									"numoutlets" : 9,
									"numvoices" : 1,
									"out" : "nnnnnnnn",
									"outlettype" : [ "", "", "", "", "", "", "", "", "bang" ],
									"patching_rect" : [ 133.0, 167.0, 220.0, 50.666664 ],
									"pitcheditrange" : [ "null" ],
									"stafflines" : [ 5 ],
									"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
									"versionnumber" : 80001,
									"voicenames" : [ "(", ")" ],
									"voicespacing" : [ -12.0, 17.6 ],
									"whole_score_data_0000000000" : [ "score", "(", "slotinfo", "(", 1, "(", "name", "velocity envelope", ")", "(", "type", "function", ")", "(", "key", 0, ")", "(", "range", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1080016896, ")", "(", "slope", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "representation", ")", "(", "grid", ")", "(", "ysnap", ")", "(", "domain", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, ")", "(", "domainslope", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "temporalmode", "relative", ")", "(", "extend", 0, ")", "(", "width", "duration", ")", "(", "height", "auto", ")", "(", "singleslotfortiednotes", 1, ")", "(", "copywhensplit", 0, ")", "(", "access", "readandwrite", ")", ")", "(", 2, "(", "name", "slot function", ")", "(", "type", "function", ")", "(", "key", 0, ")", "(", "range", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, ")", "(", "slope", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "representation", ")", "(", "grid", ")", "(", "ysnap", ")", "(", "domain", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, ")", "(", "domainslope", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "temporalmode", "relative", ")", "(", "extend", 0, ")", "(", "width", "duration", ")", "(", "height", "auto", ")", "(", "singleslotfortiednotes", 1, ")", "(", "copywhensplit", 0, ")", "(", "access", "readandwrite", ")", ")", "(", 3, "(", "name", "slot intlist", ")", "(", "type", "intlist", ")", "(", "key", 0, ")", "(", "range", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1080016896, ")", "(", "slope", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "representation", ")", "(", "default", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1078984704, ")", "(", "temporalmode", "none", ")", "(", "extend", 0, ")", "(", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", "(", "height", "auto", ")", "(", "singleslotfortiednotes", 1, ")", "(", "copywhensplit", 1, ")", "(", "access", "readandwrite", ")", ")", "(", 4, "(", "name", "slot floatlist", ")", "(", "type", "floatlist", ")", "(", "key", 0, ")", "(", "range", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, ")", "(", "slope", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "representation", ")", "(", "default", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "temporalmode", "none", ")", "(", "extend", 0, ")", "(", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", "(", "height", "auto", ")", "(", "singleslotfortiednotes", 1, ")", "(", "copywhensplit", 1, ")", "(", "access", "readandwrite", ")", ")", "(", 5, "(", "name", "slot int", ")", "(", "type", "int", ")", "(", "key", 0, ")", "(", "range", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1080016896, ")", "(", "slope", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "representation", ")", "(", "default", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1078984704, ")", "(", "temporalmode", "none", ")", "(", "extend", 0, ")", "(", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", "(", "height", "auto", ")", "(", "singleslotfortiednotes", 1, ")", "(", "copywhensplit", 1, ")", "(", "access", "readandwrite", ")", ")", "(", 6, "(", "name", "slot float", ")", "(", "type", "float", ")", "(", "key", 0, ")", "(", "range", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, ")", "(", "slope", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "representation", ")", "(", "default", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "temporalmode", "none", ")", "(", "extend", 0, ")", "(", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", "(", "height", "auto", ")", "(", "singleslotfortiednotes", 1, ")", "(", "copywhensplit", 1, ")", "(", "access", "readandwrite", ")", ")", "(", 7, "(", "name", "slot text", ")", "(", "type", "text", ")", "(", "key", 0, ")", "(", "temporalmode", "none", ")", "(", "extend", 0, ")", "(", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", "(", "height", "auto", ")", "(", "singleslotfortiednotes", 1, ")", "(", "copywhensplit", 0, ")", "(", "access", "readandwrite", ")", ")", "(", 8, "(", "name", "slot filelist", ")", "(", "type", "filelist", ")", "(", "key", 0, ")", "(", "temporalmode", "none", ")", "(", "extend", 0, ")", "(", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1080213504, ")", "(", "height", "auto", ")", "(", "singleslotfortiednotes", 1, ")", "(", "copywhensplit", 1, ")", "(", "access", "readandwrite", ")", ")", "(", 9, "(", "name", "slot spat", ")", "(", "type", "spat", ")", "(", "key", 0, ")", "(", "range", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1076101120, ")", "(", "slope", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "representation", ")", "(", "temporalmode", "relative", ")", "(", "extend", 0, ")", "(", "width", "duration", ")", "(", "height", "auto", ")", "(", "singleslotfortiednotes", 1, ")", "(", "copywhensplit", 0, ")", "(", "access", "readandwrite", ")", ")", "(", 10, "(", "name", "slot llll", ")", "(", "type", "llll", ")", "(", "key", 0, ")", "(", "temporalmode", "none", ")", "(", "extend", 0, ")", "(", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", "(", "height", "auto", ")", "(", "singleslotfortiednotes", 1, ")", "(", "copywhensplit", 0, ")", "(", "access", "readandwrite", ")", ")", "(", 11, "(", "name", "slot 11", ")", "(", "type", "none", ")", "(", "key", 0, ")", "(", "temporalmode", "none", ")", "(", "extend", 0, ")", "(", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", "(", "height", "auto", ")", "(", "singleslotfortiednotes", 1, ")", "(", "copywhensplit", 1, ")", "(", "access", "readandwrite", ")", ")", "(", 12, "(", "name", "slot 12", ")", "(", "type", "none", ")", "(", "key", 0, ")", "(", "temporalmode", "none", ")", "(", "extend", 0, ")", "(", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", "(", "height", "auto", ")", "(", "singleslotfortiednotes", 1, ")", "(", "copywhensplit", 1, ")", "(", "access", "readandwrite", ")", ")", "(", 13, "(", "name", "slot 13", ")", "(", "type", "none", ")", "(", "key", 0, ")", "(", "temporalmode", "none", ")", "(", "extend", 0, ")", "(", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", "(", "height", "auto", ")", "(", "singleslotfortiednotes", 1, ")", "(", "copywhensplit", 1, ")", "(", "access", "readandwrite", ")", ")", "(", 14, "(", "name", "slot 14", ")", "(", "type", "none", ")", "(", "key", 0, ")", "(", "temporalmode", "none", ")", "(", "extend", 0, ")", "(", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", "(", "height", "auto", ")", "(", "singleslotfortiednotes", 1, ")", "(", "copywhensplit", 1, ")", "(", "access", "readandwrite", ")", ")", "(", 15, "(", "name", "slot 15", ")", "(", "type", "none", ")", "(", "key", 0, ")", "(", "temporalmode", "none", ")", "(", "extend", 0, ")", "(", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", "(", "height", "auto", ")", "(", "singleslotfortiednotes", 1, ")", "(", "copywhensplit", 1, ")", "(", "access", "readandwrite", ")", ")", "(", 16, "(", "name", "slot 16", ")", "(", "type", "none", ")", "(", "key", 0, ")", "(", "temporalmode", "none", ")", "(", "extend", 0, ")", "(", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", "(", "height", "auto", ")", "(", "singleslotfortiednotes", 1, ")", "(", "copywhensplit", 1, ")", "(", "access", "readandwrite", ")", ")", "(", 17, "(", "name", "slot 17", ")", "(", "type", "none", ")", "(", "key", 0, ")", "(", "temporalmode", "none", ")", "(", "extend", 0, ")", "(", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", "(", "height", "auto", ")", "(", "singleslotfortiednotes", 1, ")", "(", "copywhensplit", 1, ")", "(", "access", "readandwrite", ")", ")", "(", 18, "(", "name", "slot 18", ")", "(", "type", "none", ")", "(", "key", 0, ")", "(", "temporalmode", "none", ")", "(", "extend", 0, ")", "(", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", "(", "height", "auto", ")", "(", "singleslotfortiednotes", 1, ")", "(", "copywhensplit", 1, ")", "(", "access", "readandwrite", ")", ")", "(", 19, "(", "name", "slot 19", ")", "(", "type", "none", ")", "(", "key", 0, ")", "(", "temporalmode", "none", ")", "(", "extend", 0, ")", "(", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", "(", "height", "auto", ")", "(", "singleslotfortiednotes", 1, ")", "(", "copywhensplit", 1, ")", "(", "access", "readandwrite", ")", ")", "(", 20, "(", "name", "dynamics", ")", "(", "type", "dynamics", ")", "(", "key", "d", ")", "(", "temporalmode", "none", ")", "(", "extend", 0, ")", "(", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079083008, ")", "(", "height", "auto", ")", "(", "singleslotfortiednotes", 1, ")", "(", "copywhensplit", 0, ")", "(", "access", "readandwrite", ")", ")", "(", 21, "(", "name", "lyrics", ")", "(", "type", "text", ")", "(", "key", "l", ")", "(", "temporalmode", "none", ")", "(", "extend", 0, ")", "(", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", "(", "height", "auto", ")", "(", "singleslotfortiednotes", 1, ")", "(", "copywhensplit", 0, ")", "(", "access", "readandwrite", ")", ")", "(", 22, "(", "name", "articulations", ")", "(", "type", "articulations", ")", "(", "key", "a", ")", "(", "temporalmode", "none", ")", "(", "extend", 0, ")", "(", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079738368, ")", "(", "height", "auto", ")", "(", "singleslotfortiednotes", 1, ")", "(", "copywhensplit", 1, ")", "(", "access", "readandwrite", ")", ")", "(", 23, "(", "name", "notehead", ")", "(", "type", "notehead", ")", "(", "key", "h", ")", "(", "temporalmode", "none", ")", "(", "extend", 0, ")", "(", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079738368, ")", "(", "height", "auto", ")", "(", "singleslotfortiednotes", 1, ")", "(", "copywhensplit", 1, ")", "(", "access", "readandwrite", ")", ")", "(", 24, "(", "name", "slot 24", ")", "(", "type", "none", ")", "(", "key", 0, ")", "(", "temporalmode", "none", ")", "(", "extend", 0, ")", "(", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", "(", "height", "auto", ")", "(", "singleslotfortiednotes", 1, ")", "(", "copywhensplit", 1, ")", "(", "access", "readandwrite", ")", ")", "(", 25, "(", "name", "slot 25", ")", "(", "type", "none", ")", "(", "key", 0, ")", "(", "temporalmode", "none", ")", "(", "extend", 0, ")", "(", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", "(", "height", "auto", ")", "(", "singleslotfortiednotes", 1, ")", "(", "copywhensplit", 1, ")", "(", "access", "readandwrite", ")", ")", "(", 26, "(", "name", "slot 26", ")", "(", "type", "none", ")", "(", "key", 0, ")", "(", "temporalmode", "none", ")", "(", "extend", 0, ")", "(", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", "(", "height", "auto", ")", "(", "singleslotfortiednotes", 1, ")", "(", "copywhensplit", 1, ")", "(", "access", "readandwrite", ")", ")", "(", 27, "(", "name", "slot 27", ")", "(", "type", "none", ")", "(", "key", 0, ")", "(", "temporalmode", "none", ")", "(", "extend", 0, ")", "(", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", "(", "height", "auto", ")", "(", "singleslotfortiednotes", 1, ")", "(", "copywhensplit", 1, ")", "(", "access", "readandwrite", ")", ")", "(", 28, "(", "name", "slot 28", ")", "(", "type", "none", ")", "(", "key", 0, ")", "(", "temporalmode", "none", ")", "(", "extend", 0, ")", "(", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", "(", "height", "auto", ")", "(", "singleslotfortiednotes", 1, ")", "(", "copywhensplit", 1, ")", "(", "access", "readandwrite", ")", ")", "(", 29, "(", "name", "slot 29", ")", "(", "type", "none", ")", "(", "key", 0, ")", "(", "temporalmode", "none", ")", "(", "extend", 0, ")", "(", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", "(", "height", "auto", ")", "(", "singleslotfortiednotes", 1, ")", "(", "copywhensplit", 1, ")", "(", "access", "readandwrite", ")", ")", "(", 30, "(", "name", "slot 30", ")", "(", "type", "none", ")", "(", "key", 0, ")", "(", "temporalmode", "none", ")", "(", "extend", 0, ")", "(", "width", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", "(", "height", "auto", ")", "(", "singleslotfortiednotes", 1, ")", "(", "copywhensplit", 1, ")", "(", "access", "readandwrite", ")", ")", ")", "(", "commands", "(", 1, "(", "note", "note", ")", "(", "chord", "chord", ")", "(", "rest", "rest", ")", "(", "key", 0, ")", ")", "(", 2, "(", "note", "note", ")", "(", "chord", "chord", ")", "(", "rest", "rest", ")", "(", "key", 0, ")", ")", "(", 3, "(", "note", "note", ")", "(", "chord", "chord", ")", "(", "rest", "rest", ")", "(", "key", 0, ")", ")", "(", 4, "(", "note", "note", ")", "(", "chord", "chord", ")", "(", "rest", "rest", ")", "(", "key", 0, ")", ")", "(", 5, "(", "note", "note", ")", "(", "chord", "chord", ")", "(", "rest", "rest", ")", "(", "key", 0, ")", ")", ")", "(", "markers", ")", "(", "midichannels", 1, ")", "(", "articulationinfo", ")", "(", "noteheadinfo", ")", "(", "(", "(", "(", 4, 4, ")", "(", "(", "1/4", 110, ")", ")", ")", "(", "leveltype", 1, ")", "(", "(", "leveltype", 8, ")", "(", "1/16", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1086070784, 100, 0, 0, ")", 0, ")", "(", "1/16", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1085942784, 100, 0, 0, ")", 0, ")", "(", "1/16", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1085993984, 100, 0, 0, ")", 0, ")", "(", "1/16", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1086045184, 100, 0, 0, ")", 0, ")", ")", "(", "(", "leveltype", 8, ")", "(", "1/16", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1086070784, 100, 0, 0, ")", 0, ")", "(", "1/16", "(", "Ab5", 100, 0, 0, ")", 0, ")", "(", "1/16", "(", "Bb5", 100, 0, 0, ")", 0, ")", "(", "1/16", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1086070784, 100, 0, 0, ")", 0, ")", ")", "(", "(", "leveltype", 8, ")", "(", "1/16", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1086121984, 100, 0, 0, ")", 0, ")", "(", "1/16", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1086045184, 100, 0, 0, ")", 0, ")", "(", "1/16", "(", "C#6", 100, 0, 0, ")", 0, ")", "(", "1/16", "(", "D#6", 100, 0, 0, ")", 0, ")", ")", "(", "(", "leveltype", 8, ")", "(", "1/8", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1086173184, 100, 0, 0, ")", 0, ")", "(", "-1/8", 0, ")", ")", 0, ")", 0, ")" ],
									"whole_score_data_count" : [ 1 ]
								}

							}
, 							{
								"box" : 								{
									"attr" : "mode",
									"id" : "obj-4",
									"maxclass" : "attrui",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 11.647934, 106.0, 277.0, 23.0 ],
									"style" : ""
								}

							}
, 							{
								"box" : 								{
									"attr" : "type",
									"id" : "obj-29",
									"maxclass" : "attrui",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 11.647934, 131.0, 260.0, 23.0 ],
									"style" : ""
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-8",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 140.5, 248.0, 35.0, 23.0 ],
									"style" : "",
									"text" : "stop"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-7",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 100.5, 248.0, 34.0, 23.0 ],
									"style" : "",
									"text" : "play"
								}

							}
, 							{
								"box" : 								{
									"bounce_data_0000000000" : [ "bounce", "(", "room", "(", "vertices", "(", "(", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079439441, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1077918611, ")", "(", "label", "score", ")", "(", "score", ")", ")", "(", "(", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3226992132, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079808216, ")", "(", "label", "score", ")", "(", "score", ")", ")", "(", "(", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3226992132, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3227452148, ")", "(", "label", "score", ")", "(", "score", ")", ")", ")", "(", "edges", "(", 1, 2, "(", "label", "lowscore", ")", "(", "score", "score", "(", "(", "(", "(", 4, 4, ")", "(", "(", "1/4", 110, ")", ")", ")", "(", "leveltype", 1, ")", "(", "(", "leveltype", 8, ")", "(", "1/16", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1086070784, 100, 0, 0, ")", 0, ")", "(", "1/16", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1085942784, 100, 0, 0, ")", 0, ")", "(", "1/16", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1085993984, 100, 0, 0, ")", 0, ")", "(", "1/16", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1086045184, 100, 0, 0, ")", 0, ")", ")", "(", "(", "leveltype", 8, ")", "(", "1/16", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1086070784, 100, 0, 0, ")", 0, ")", "(", "1/16", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1085968384, 100, 0, "(", "graphic", 6900, "-1/2", ")", 0, ")", 0, ")", "(", "1/16", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1086019584, 100, 0, "(", "graphic", 7100, "-1/2", ")", 0, ")", 0, ")", "(", "1/16", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1086070784, 100, 0, 0, ")", 0, ")", ")", "(", "(", "leveltype", 8, ")", "(", "1/16", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1086121984, 100, 0, 0, ")", 0, ")", "(", "1/16", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1086045184, 100, 0, 0, ")", 0, ")", "(", "1/16", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1086096384, 100, 0, "(", "graphic", 7200, "1/2", ")", 0, ")", 0, ")", "(", "1/16", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1086147584, 100, 0, "(", "graphic", 7400, "1/2", ")", 0, ")", 0, ")", ")", "(", "(", "leveltype", 8, ")", "(", "1/8", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1086173184, 100, 0, 0, ")", 0, ")", "(", "-1/8", 0, ")", ")", 0, ")", 0, ")", ")", ")", "(", 2, 3, "(", "label", "score", ")", "(", "score", "score", "(", "(", "(", "(", 4, 4, ")", "(", "(", "1/4", 130, ")", ")", ")", "(", "leveltype", 1, ")", "(", "(", "leveltype", 8, ")", "(", "-1/16", 0, ")", "(", "(", "leveltype", 1, ")", "(", "1/16", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1086045184, 100, 0, 0, ")", 0, ")", "(", "1/16", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1086173184, 100, 0, 0, ")", 0, ")", "(", "1/16", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1086275584, 100, 0, "(", "graphic", 7900, "1/2", ")", 0, ")", 0, ")", ")", ")", "(", "(", "leveltype", 8, ")", "(", "1/8", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1086338560, 100, 0, 0, ")", 0, ")", "(", "(", "leveltype", 1, ")", "(", "1/16", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1086275584, 100, 0, "(", "graphic", 7900, "1/2", ")", 0, ")", 0, ")", "(", "1/16", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1086338560, 100, 0, 0, ")", 0, ")", ")", ")", "(", "-1/2", 0, ")", 0, ")", 0, ")", ")", ")", "(", 3, 1, "(", "label", "score", ")", "(", "score", "score", "(", "(", "(", "(", 4, 4, ")", "(", "(", "1/4", 120, ")", ")", ")", "(", "leveltype", 1, ")", "(", "(", "leveltype", 8, ")", "(", "1/8", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1086096384, 100, 0, 0, ")", 0, ")", "(", "1/8", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1086096384, 100, 0, 0, ")", 0, ")", ")", "(", "(", "leveltype", 8, ")", "(", "1/8", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1086096384, 100, 0, 0, ")", 0, ")", "(", "1/8", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1086096384, 100, 0, 0, ")", 0, ")", ")", "(", "(", "leveltype", 8, ")", "(", "1/8", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1086096384, 100, 0, 0, ")", 0, ")", "(", "1/8", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1086096384, 100, 0, 0, ")", 0, ")", ")", "(", "(", "leveltype", 8, ")", "(", "1/8", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1086096384, 100, 0, 0, ")", 0, ")", "(", "1/8", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1086096384, 100, 0, 0, ")", 0, ")", ")", 0, ")", 0, ")", ")", ")", ")", ")", "(", "balls", "(", "(", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 3226642054, "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 3222978505, ")", "(", "speed", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 3224828794, "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1080087810, ")", "(", "color", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1071225241, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, ")", "(", "channel", 1, ")", "(", "flags", ")", ")", ")" ],
									"bounce_data_count" : [ 1 ],
									"center" : [ -11.511646, -7.573449 ],
									"id" : "obj-1",
									"maxclass" : "dada.bounce",
									"numinlets" : 2,
									"numoutlets" : 5,
									"out" : "nnnn",
									"outlettype" : [ "", "", "", "", "bang" ],
									"patching_rect" : [ 44.5, 305.0, 204.0, 184.0 ],
									"showgrid" : 1,
									"type" : 1,
									"versionnumber" : 10000,
									"zoom" : 57.948766
								}

							}
, 							{
								"box" : 								{
									"border" : 0,
									"filename" : "helpname.js",
									"id" : "obj-2",
									"ignoreclick" : 1,
									"jsarguments" : [ "dada.bounce" ],
									"maxclass" : "jsui",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 10.0, 10.0, 273.295868, 57.567627 ]
								}

							}
 ],
						"lines" : [ 							{
								"patchline" : 								{
									"destination" : [ "obj-24", 0 ],
									"source" : [ "obj-1", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-5", 0 ],
									"source" : [ "obj-1", 3 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-14", 1 ],
									"source" : [ "obj-10", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-14", 2 ],
									"source" : [ "obj-11", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-3", 0 ],
									"source" : [ "obj-12", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-10", 0 ],
									"order" : 1,
									"source" : [ "obj-13", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-11", 0 ],
									"order" : 0,
									"source" : [ "obj-13", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-9", 0 ],
									"order" : 2,
									"source" : [ "obj-13", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-15", 0 ],
									"source" : [ "obj-14", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-1", 0 ],
									"source" : [ "obj-15", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-1", 0 ],
									"source" : [ "obj-18", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-1", 0 ],
									"source" : [ "obj-27", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-1", 0 ],
									"source" : [ "obj-29", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-16", 0 ],
									"source" : [ "obj-3", 7 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-1", 0 ],
									"source" : [ "obj-4", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-12", 0 ],
									"order" : 1,
									"source" : [ "obj-5", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-3", 0 ],
									"order" : 0,
									"source" : [ "obj-5", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-1", 0 ],
									"source" : [ "obj-7", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-1", 0 ],
									"source" : [ "obj-8", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-14", 0 ],
									"source" : [ "obj-9", 0 ]
								}

							}
 ]
					}
,
					"patching_rect" : [ 123.0, 325.0, 56.0, 22.0 ],
					"saved_object_attributes" : 					{
						"description" : "",
						"digest" : "",
						"fontsize" : 13.0,
						"globalpatchername" : "",
						"style" : "",
						"tags" : ""
					}
,
					"style" : "",
					"text" : "p scores",
					"varname" : "basic_tab[7]"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"id" : "obj-10",
					"maxclass" : "newobj",
					"numinlets" : 0,
					"numoutlets" : 0,
					"patcher" : 					{
						"fileversion" : 1,
						"appversion" : 						{
							"major" : 7,
							"minor" : 3,
							"revision" : 4,
							"architecture" : "x64",
							"modernui" : 1
						}
,
						"rect" : [ 0.0, 26.0, 703.0, 533.0 ],
						"bglocked" : 0,
						"openinpresentation" : 0,
						"default_fontsize" : 13.0,
						"default_fontface" : 0,
						"default_fontname" : "Arial",
						"gridonopen" : 1,
						"gridsize" : [ 5.0, 5.0 ],
						"gridsnaponopen" : 1,
						"objectsnaponopen" : 1,
						"statusbarvisible" : 2,
						"toolbarvisible" : 1,
						"lefttoolbarpinned" : 0,
						"toptoolbarpinned" : 0,
						"righttoolbarpinned" : 0,
						"bottomtoolbarpinned" : 0,
						"toolbars_unpinned_last_save" : 0,
						"tallnewobj" : 0,
						"boxanimatetime" : 200,
						"enablehscroll" : 1,
						"enablevscroll" : 1,
						"devicewidth" : 0.0,
						"description" : "",
						"digest" : "",
						"tags" : "",
						"style" : "",
						"subpatcher_template" : "",
						"showontab" : 1,
						"boxes" : [ 							{
								"box" : 								{
									"attr" : "mode",
									"id" : "obj-29",
									"maxclass" : "attrui",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 181.5, 69.567627, 274.0, 23.0 ],
									"style" : ""
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-27",
									"maxclass" : "newobj",
									"numinlets" : 3,
									"numoutlets" : 2,
									"outlettype" : [ "", "int" ],
									"patching_rect" : [ 410.5, 391.0, 104.0, 23.0 ],
									"style" : "",
									"text" : "bach.ezmidiplay"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-26",
									"linecount" : 2,
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 10.0, 79.0, 124.647934, 36.0 ],
									"style" : "",
									"text" : "Here's an example of feedback loop.",
									"textcolor" : [ 0.501961, 0.501961, 0.501961, 1.0 ]
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-25",
									"maxclass" : "preset",
									"numinlets" : 1,
									"numoutlets" : 4,
									"outlettype" : [ "preset", "int", "preset", "int" ],
									"patching_rect" : [ 500.0, 101.0, 31.0, 19.0 ],
									"preset_data" : [ 										{
											"number" : 1,
											"data" : [ 5, "obj-1", "dada.bounce", "begin_preset", 174, 180, "obj-1", "dada.bounce", "restore_preset", 0, 174, "setstoredstate", "(", "room", "(", "(", "vertices", "(", "(", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 62094, 1079745133, "_x_x_x_x_bach_float64_x_x_x_x_", 63194, 3222507751, ")", "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1086006784, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", "(", "(", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 25820, 3226992132, "_x_x_x_x_bach_float64_x_x_x_x_", 23841, 1079808216, ")", "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1085763584, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", "(", "(", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 51266, 3226992132, "_x_x_x_x_bach_float64_x_x_x_x_", 32257, 3227452148, ")", "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1085320704, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", ")", "(", "edges", "(", 1, 2, "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1085763584, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", "(", 2, 3, "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1085037568, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", "(", 3, 1, "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 52350, 1086250484, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", ")", ")", ")", "(", "balls", "(", "(", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 3860, 3226437095, "_x_x_x_x_bach_float64_x_x_x_x_", 40332, 3226746579, ")", "(", "speed", "_x_x_x_x_bach_float64_x_x_x_x_", 42934, 1079327334, "_x_x_x_x_bach_float64_x_x_x_x_", 59320, 3227172977, ")", "(", "color", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 39322, 1071225241, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, ")", "(", "channel", 1, ")", "(", "flags", ")", ")", ")", 4, "obj-1", "dada.bounce", "end_preset" ]
										}
 ],
									"style" : ""
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-22",
									"maxclass" : "newobj",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 28.647934, 368.0, 69.0, 23.0 ],
									"style" : "",
									"text" : "bach.* 0.1"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-21",
									"maxclass" : "newobj",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 28.647934, 338.0, 61.0, 23.0 ],
									"saved_object_attributes" : 									{
										"embed" : 0,
										"versionnumber" : 80001
									}
,
									"style" : "",
									"text" : "bach.reg"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-19",
									"maxclass" : "newobj",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 16.647934, 402.0, 128.0, 23.0 ],
									"saved_object_attributes" : 									{
										"versionnumber" : 80001
									}
,
									"style" : "",
									"text" : "bach.join @out t"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-17",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 2,
									"outlettype" : [ "int", "bang" ],
									"patching_rect" : [ 16.647934, 305.0, 31.0, 23.0 ],
									"style" : "",
									"text" : "t i b"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-16",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 16.647934, 443.0, 145.0, 23.0 ],
									"style" : "",
									"text" : "move edge $1 ( $2 $3 )"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-6",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 2,
									"outlettype" : [ "", "bang" ],
									"patching_rect" : [ 16.647934, 273.0, 144.0, 23.0 ],
									"saved_object_attributes" : 									{
										"versionnumber" : 80001
									}
,
									"style" : "",
									"text" : "bach.keys edge @out t"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-4",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 16.647934, 240.0, 76.0, 23.0 ],
									"saved_object_attributes" : 									{
										"versionnumber" : 80001
									}
,
									"style" : "",
									"text" : "bach.pick 1"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-14",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 2,
									"outlettype" : [ "", "bang" ],
									"patching_rect" : [ 16.647934, 206.0, 128.0, 23.0 ],
									"saved_object_attributes" : 									{
										"versionnumber" : 80001
									}
,
									"style" : "",
									"text" : "bach.keys subdivide"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-12",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 2,
									"outlettype" : [ "", "bang" ],
									"patching_rect" : [ 16.647934, 177.0, 102.0, 23.0 ],
									"saved_object_attributes" : 									{
										"versionnumber" : 80001
									}
,
									"style" : "",
									"text" : "bach.keys edge"
								}

							}
, 							{
								"box" : 								{
									"bubble" : 1,
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-11",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 390.0, 458.0, 254.0, 25.0 ],
									"style" : "",
									"text" : "Feedback operations must be deferred!"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-10",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 345.0, 458.0, 40.0, 23.0 ],
									"style" : "",
									"text" : "defer"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-5",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 344.5, 488.0, 127.0, 23.0 ],
									"style" : "",
									"text" : "subdivide edge $1 3"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-3",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 3,
									"outlettype" : [ "", "", "bang" ],
									"patching_rect" : [ 344.5, 420.0, 183.0, 23.0 ],
									"saved_object_attributes" : 									{
										"versionnumber" : 80001
									}
,
									"style" : "",
									"text" : "bach.keys edge speed @out t"
								}

							}
, 							{
								"box" : 								{
									"bubble" : 1,
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-9",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 301.5, 98.0, 163.0, 25.0 ],
									"style" : "",
									"text" : "Start/stop sequencing"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-8",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 252.5, 98.0, 35.0, 23.0 ],
									"style" : "",
									"text" : "stop"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-7",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 212.5, 98.0, 34.0, 23.0 ],
									"style" : "",
									"text" : "play"
								}

							}
, 							{
								"box" : 								{
									"bounce_data_0000000000" : [ "bounce", "(", "room", "(", "vertices", "(", "(", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079745133, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3222507751, ")", "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1086006784, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", "(", "(", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3226992132, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079808216, ")", "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1085763584, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", "(", "(", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3226992132, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3227452148, ")", "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1085320704, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", ")", "(", "edges", "(", 1, 2, "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1085763584, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", "(", 2, 3, "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1085037568, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", "(", 3, 1, "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1086250484, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", ")", ")", "(", "balls", "(", "(", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3224961092, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1075309054, ")", "(", "speed", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1078245580, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1080051018, ")", "(", "color", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1071225241, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, ")", "(", "channel", 1, ")", "(", "flags", ")", ")", ")" ],
									"bounce_data_count" : [ 1 ],
									"id" : "obj-1",
									"maxclass" : "dada.bounce",
									"mode" : 1,
									"numinlets" : 2,
									"numoutlets" : 5,
									"out" : "nnnn",
									"outlettype" : [ "", "", "", "", "bang" ],
									"patching_rect" : [ 212.5, 138.0, 283.0, 242.0 ],
									"showgrid" : 1,
									"versionnumber" : 10000,
									"zoom" : 91.996155
								}

							}
, 							{
								"box" : 								{
									"border" : 0,
									"filename" : "helpname.js",
									"id" : "obj-2",
									"ignoreclick" : 1,
									"jsarguments" : [ "dada.bounce" ],
									"maxclass" : "jsui",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 10.0, 10.0, 273.295868, 57.567627 ]
								}

							}
 ],
						"lines" : [ 							{
								"patchline" : 								{
									"destination" : [ "obj-12", 0 ],
									"midpoints" : [ 288.0, 491.0, 9.698967, 491.0, 9.698967, 166.0, 26.147934, 166.0 ],
									"source" : [ "obj-1", 1 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-27", 0 ],
									"source" : [ "obj-1", 3 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-3", 0 ],
									"source" : [ "obj-1", 2 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-5", 0 ],
									"source" : [ "obj-10", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-14", 0 ],
									"source" : [ "obj-12", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-4", 0 ],
									"source" : [ "obj-14", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-1", 0 ],
									"midpoints" : [ 26.147934, 479.0, 182.0, 479.0, 182.0, 135.0, 222.0, 135.0 ],
									"source" : [ "obj-16", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-19", 0 ],
									"source" : [ "obj-17", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-21", 0 ],
									"source" : [ "obj-17", 1 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-16", 0 ],
									"source" : [ "obj-19", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-22", 0 ],
									"source" : [ "obj-21", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-19", 1 ],
									"source" : [ "obj-22", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-1", 0 ],
									"source" : [ "obj-25", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-1", 0 ],
									"source" : [ "obj-29", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-10", 0 ],
									"source" : [ "obj-3", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-21", 1 ],
									"midpoints" : [ 436.0, 453.0, 195.073967, 453.0, 195.073967, 327.0, 80.147934, 327.0 ],
									"source" : [ "obj-3", 1 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-6", 0 ],
									"source" : [ "obj-4", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-1", 0 ],
									"midpoints" : [ 354.0, 521.0, 183.25, 521.0, 183.25, 134.0, 222.0, 134.0 ],
									"source" : [ "obj-5", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-17", 0 ],
									"source" : [ "obj-6", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-1", 0 ],
									"source" : [ "obj-7", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-1", 0 ],
									"source" : [ "obj-8", 0 ]
								}

							}
 ]
					}
,
					"patching_rect" : [ 105.0, 292.0, 69.0, 22.0 ],
					"saved_object_attributes" : 					{
						"description" : "",
						"digest" : "",
						"fontsize" : 13.0,
						"globalpatchername" : "",
						"style" : "",
						"tags" : ""
					}
,
					"style" : "",
					"text" : "p feedback",
					"varname" : "basic_tab[6]"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"id" : "obj-9",
					"maxclass" : "newobj",
					"numinlets" : 0,
					"numoutlets" : 0,
					"patcher" : 					{
						"fileversion" : 1,
						"appversion" : 						{
							"major" : 7,
							"minor" : 3,
							"revision" : 4,
							"architecture" : "x64",
							"modernui" : 1
						}
,
						"rect" : [ 0.0, 26.0, 703.0, 533.0 ],
						"bglocked" : 0,
						"openinpresentation" : 0,
						"default_fontsize" : 13.0,
						"default_fontface" : 0,
						"default_fontname" : "Arial",
						"gridonopen" : 1,
						"gridsize" : [ 5.0, 5.0 ],
						"gridsnaponopen" : 1,
						"objectsnaponopen" : 1,
						"statusbarvisible" : 2,
						"toolbarvisible" : 1,
						"lefttoolbarpinned" : 0,
						"toptoolbarpinned" : 0,
						"righttoolbarpinned" : 0,
						"bottomtoolbarpinned" : 0,
						"toolbars_unpinned_last_save" : 0,
						"tallnewobj" : 0,
						"boxanimatetime" : 200,
						"enablehscroll" : 1,
						"enablevscroll" : 1,
						"devicewidth" : 0.0,
						"description" : "",
						"digest" : "",
						"tags" : "",
						"style" : "",
						"subpatcher_template" : "",
						"showontab" : 1,
						"boxes" : [ 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-29",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 261.0, 148.0, 72.0, 21.0 ],
									"style" : "",
									"text" : "Save/load:",
									"textcolor" : [ 0.501961, 0.501961, 0.501961, 1.0 ]
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-27",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 264.0, 219.5, 52.0, 23.0 ],
									"style" : "",
									"text" : "writetxt"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-26",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 264.0, 167.5, 37.0, 23.0 ],
									"style" : "",
									"text" : "read"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-25",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 264.0, 194.5, 38.0, 23.0 ],
									"style" : "",
									"text" : "write"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-23",
									"linecount" : 2,
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 100.0, 488.0, 284.0, 36.0 ],
									"style" : "",
									"text" : "When a ball is added via \"addball\", its assigned index is sent through the notification outlet",
									"textcolor" : [ 0.501961, 0.501961, 0.501961, 1.0 ]
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-22",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 383.75, 494.0, 105.0, 23.0 ],
									"saved_object_attributes" : 									{
										"versionnumber" : 80001
									}
,
									"style" : "",
									"text" : "bach.print Notify"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-21",
									"linecount" : 3,
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 411.0, 176.0, 248.0, 50.0 ],
									"style" : "",
									"text" : "You can use any of the specifications in the ball syntax (see reference, or \"dump\" message output)",
									"textcolor" : [ 0.501961, 0.501961, 0.501961, 1.0 ]
								}

							}
, 							{
								"box" : 								{
									"bubble" : 1,
									"bubblepoint" : 0.99,
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-20",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 561.0, 112.5, 85.0, 25.0 ],
									"style" : "",
									"text" : "Add a ball"
								}

							}
, 							{
								"box" : 								{
									"bubble" : 1,
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-19",
									"linecount" : 2,
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 204.0, 100.5, 133.0, 40.0 ],
									"style" : "",
									"text" : "Only dump graph room or balls"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-18",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 122.0, 109.0, 73.0, 23.0 ],
									"style" : "",
									"text" : "dump balls"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-16",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 39.0, 109.0, 76.0, 23.0 ],
									"style" : "",
									"text" : "dump room"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-15",
									"linecount" : 3,
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 399.0, 122.0, 155.0, 52.0 ],
									"style" : "",
									"text" : "addball (coord 100 100) (speed -200 -200) (color 0.5 0.5 0 1)"
								}

							}
, 							{
								"box" : 								{
									"bubble" : 1,
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-14",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 509.5, 229.5, 118.0, 25.0 ],
									"style" : "",
									"text" : "Delete 2nd ball "
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-5",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 424.5, 229.5, 77.0, 23.0 ],
									"style" : "",
									"text" : "deleteball 2"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-13",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 10.0, 395.5, 190.0, 23.0 ],
									"saved_object_attributes" : 									{
										"versionnumber" : 80001
									}
,
									"style" : "",
									"text" : "bach.post Dump @maxdepth 1"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-12",
									"linecount" : 3,
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 10.0, 436.0, 297.0, 50.0 ],
									"style" : "",
									"text" : "Output content is human-readable, however the full syntax is also explained in the object reference.",
									"textcolor" : [ 0.501961, 0.501961, 0.501961, 1.0 ]
								}

							}
, 							{
								"box" : 								{
									"bubble" : 1,
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-11",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 62.5, 74.0, 280.0, 25.0 ],
									"style" : "",
									"text" : "Dump all the information from the first outlet"
								}

							}
, 							{
								"box" : 								{
									"bubble" : 1,
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-10",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 459.0, 78.0, 95.0, 25.0 ],
									"style" : "",
									"text" : "Delete balls"
								}

							}
, 							{
								"box" : 								{
									"bubble" : 1,
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-9",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 447.0, 53.0, 192.0, 25.0 ],
									"style" : "",
									"text" : "Delete graph room elements"
								}

							}
, 							{
								"box" : 								{
									"bubble" : 1,
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-17",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 394.0, 21.0, 138.0, 25.0 ],
									"style" : "",
									"text" : "Delete all elements"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-8",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 385.0, 78.0, 69.0, 23.0 ],
									"style" : "",
									"text" : "clear balls"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-7",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 367.0, 53.0, 72.0, 23.0 ],
									"style" : "",
									"text" : "clear room"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-6",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 351.0, 23.0, 39.0, 23.0 ],
									"style" : "",
									"text" : "clear"
								}

							}
, 							{
								"box" : 								{
									"bounce_data_0000000000" : [ "bounce", "(", "room", "(", "vertices", ")", "(", "edges", ")", ")", "(", "balls", ")" ],
									"bounce_data_count" : [ 1 ],
									"id" : "obj-3",
									"maxclass" : "dada.bounce",
									"numinlets" : 2,
									"numoutlets" : 5,
									"out" : "nnnn",
									"outlettype" : [ "", "", "", "", "bang" ],
									"patching_rect" : [ 331.0, 262.0, 230.0, 224.0 ],
									"showgrid" : 1,
									"versionnumber" : 10000
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-4",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 10.0, 74.0, 43.0, 23.0 ],
									"style" : "",
									"text" : "dump"
								}

							}
, 							{
								"box" : 								{
									"bounce_data_0000000000" : [ "bounce", "(", "room", "(", "vertices", "(", "(", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1077691405, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1078895864, ")", "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1085763584, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", "(", "(", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3226201111, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1080175813, ")", "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1085763584, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", "(", "(", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3227614861, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1078895864, ")", "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1085763584, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", "(", "(", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3226201111, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3224818249, ")", "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1085763584, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", "(", "(", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079918120, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1071295504, ")", "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1085763584, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", "(", "(", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1078355975, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079660378, ")", "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1085763584, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", "(", "(", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3226704514, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079004381, ")", "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1085763584, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", "(", "(", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3226704514, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3226474372, ")", "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1085763584, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", "(", "(", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1078355975, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3227130369, ")", "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1085763584, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", ")", "(", "edges", "(", 1, 2, "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1085763584, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", "(", 2, 3, "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1086070784, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", "(", 3, 4, "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1086250484, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", "(", 4, 1, "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1086351360, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", "(", 5, 6, "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1085763584, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", "(", 6, 7, "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1086070784, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", "(", 7, 8, "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1086250484, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", "(", 8, 9, "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1086351360, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", "(", 9, 5, "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1086400808, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", ")", ")", "(", "balls", "(", "(", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3226503461, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079234633, ")", "(", "speed", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "color", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1071225241, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, ")", "(", "channel", 1, ")", "(", "flags", ")", ")", "(", "(", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1077833633, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3226241191, ")", "(", "speed", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1078535961, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1080016962, ")", "(", "color", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1071225241, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, ")", "(", "channel", 1, ")", "(", "flags", ")", ")", ")" ],
									"bounce_data_count" : [ 1 ],
									"center" : [ 8.716064, -15.008973 ],
									"id" : "obj-1",
									"maxclass" : "dada.bounce",
									"numinlets" : 2,
									"numoutlets" : 5,
									"out" : "nnnn",
									"outlettype" : [ "", "", "", "", "bang" ],
									"patching_rect" : [ 10.0, 147.0, 247.0, 222.0 ],
									"showgrid" : 1,
									"versionnumber" : 10000,
									"zoom" : 89.597699
								}

							}
, 							{
								"box" : 								{
									"border" : 0,
									"filename" : "helpname.js",
									"id" : "obj-2",
									"ignoreclick" : 1,
									"jsarguments" : [ "dada.bounce" ],
									"maxclass" : "jsui",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 10.0, 10.0, 273.295868, 57.567627 ]
								}

							}
 ],
						"lines" : [ 							{
								"patchline" : 								{
									"destination" : [ "obj-13", 0 ],
									"order" : 1,
									"source" : [ "obj-1", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-3", 0 ],
									"midpoints" : [ 19.5, 383.0, 277.0, 383.0, 277.0, 251.0, 340.5, 251.0 ],
									"order" : 0,
									"source" : [ "obj-1", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-3", 0 ],
									"source" : [ "obj-15", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-1", 0 ],
									"source" : [ "obj-16", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-1", 0 ],
									"source" : [ "obj-18", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-1", 0 ],
									"source" : [ "obj-25", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-1", 0 ],
									"source" : [ "obj-26", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-1", 0 ],
									"source" : [ "obj-27", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-22", 0 ],
									"source" : [ "obj-3", 1 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-1", 0 ],
									"source" : [ "obj-4", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-3", 0 ],
									"source" : [ "obj-5", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-3", 0 ],
									"source" : [ "obj-6", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-3", 0 ],
									"source" : [ "obj-7", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-3", 0 ],
									"source" : [ "obj-8", 0 ]
								}

							}
 ]
					}
,
					"patching_rect" : [ 32.0, 151.0, 115.0, 22.0 ],
					"saved_object_attributes" : 					{
						"description" : "",
						"digest" : "",
						"fontsize" : 13.0,
						"globalpatchername" : "",
						"style" : "",
						"tags" : ""
					}
,
					"style" : "",
					"text" : "p \"basic messages\"",
					"varname" : "basic_tab[5]"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"id" : "obj-7",
					"maxclass" : "newobj",
					"numinlets" : 0,
					"numoutlets" : 0,
					"patcher" : 					{
						"fileversion" : 1,
						"appversion" : 						{
							"major" : 7,
							"minor" : 3,
							"revision" : 4,
							"architecture" : "x64",
							"modernui" : 1
						}
,
						"rect" : [ 0.0, 26.0, 703.0, 533.0 ],
						"bglocked" : 0,
						"openinpresentation" : 0,
						"default_fontsize" : 13.0,
						"default_fontface" : 0,
						"default_fontname" : "Arial",
						"gridonopen" : 1,
						"gridsize" : [ 5.0, 5.0 ],
						"gridsnaponopen" : 1,
						"objectsnaponopen" : 1,
						"statusbarvisible" : 2,
						"toolbarvisible" : 1,
						"lefttoolbarpinned" : 0,
						"toptoolbarpinned" : 0,
						"righttoolbarpinned" : 0,
						"bottomtoolbarpinned" : 0,
						"toolbars_unpinned_last_save" : 0,
						"tallnewobj" : 0,
						"boxanimatetime" : 200,
						"enablehscroll" : 1,
						"enablevscroll" : 1,
						"devicewidth" : 0.0,
						"description" : "",
						"digest" : "",
						"tags" : "",
						"style" : "",
						"subpatcher_template" : "",
						"showontab" : 1,
						"boxes" : [ 							{
								"box" : 								{
									"id" : "obj-13",
									"maxclass" : "newobj",
									"numinlets" : 3,
									"numoutlets" : 2,
									"outlettype" : [ "", "int" ],
									"patching_rect" : [ 218.25, 489.0, 104.0, 23.0 ],
									"style" : "",
									"text" : "bach.ezmidiplay"
								}

							}
, 							{
								"box" : 								{
									"bubble" : 1,
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-27",
									"linecount" : 2,
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 464.0, 10.0, 171.0, 40.0 ],
									"style" : "",
									"text" : "Microtonal division (as for bach.roll/bach.score)"
								}

							}
, 							{
								"box" : 								{
									"attr" : "tonedivision",
									"id" : "obj-26",
									"maxclass" : "attrui",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 305.0, 22.0, 150.0, 23.0 ],
									"style" : ""
								}

							}
, 							{
								"box" : 								{
									"bubble" : 1,
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-25",
									"linecount" : 4,
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 464.0, 51.5, 171.0, 69.0 ],
									"style" : "",
									"text" : "Is velocity dampened depending on the hitting angle between ball and edge?"
								}

							}
, 							{
								"box" : 								{
									"attr" : "speedvel",
									"id" : "obj-15",
									"maxclass" : "attrui",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 305.0, 74.5, 150.0, 23.0 ],
									"style" : ""
								}

							}
, 							{
								"box" : 								{
									"bubble" : 1,
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-24",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 433.0, 235.0, 86.0, 25.0 ],
									"style" : "",
									"text" : "Remove it"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-23",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 389.0, 235.0, 40.0, 23.0 ],
									"style" : "",
									"text" : "clock"
								}

							}
, 							{
								"box" : 								{
									"bubble" : 1,
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-21",
									"linecount" : 3,
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 471.0, 183.5, 146.0, 54.0 ],
									"style" : "",
									"text" : "Assign an external setclock object as clock master"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-3",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 324.0, 271.0, 57.0, 21.0 ],
									"style" : "",
									"text" : "1.5 ms -",
									"textcolor" : [ 0.501961, 0.501961, 0.501961, 1.0 ]
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-16",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 334.0, 318.0, 47.0, 21.0 ],
									"style" : "",
									"text" : "1 ms -",
									"textcolor" : [ 0.501961, 0.501961, 0.501961, 1.0 ]
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"format" : 6,
									"id" : "obj-18",
									"maxclass" : "flonum",
									"numinlets" : 1,
									"numoutlets" : 2,
									"outlettype" : [ "", "bang" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 382.0, 444.0, 54.0, 23.0 ],
									"style" : "",
									"triscale" : 0.9
								}

							}
, 							{
								"box" : 								{
									"floatoutput" : 1,
									"id" : "obj-19",
									"maxclass" : "slider",
									"numinlets" : 1,
									"numoutlets" : 1,
									"orientation" : 2,
									"outlettype" : [ "" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 382.0, 275.0, 16.0, 157.0 ],
									"relative" : 1,
									"size" : 1.5,
									"style" : ""
								}

							}
, 							{
								"box" : 								{
									"bubble" : 1,
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-20",
									"linecount" : 5,
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 408.0, 302.0, 117.0, 83.0 ],
									"style" : "",
									"text" : "move the slider to change the \"millisecond\" for the external setclock"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-10",
									"maxclass" : "newobj",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 382.0, 474.0, 148.0, 23.0 ],
									"style" : "",
									"text" : "setclock binky mul 0.82"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-22",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 333.0, 414.0, 48.0, 21.0 ],
									"style" : "",
									"text" : "0 ms -",
									"textcolor" : [ 0.501961, 0.501961, 0.501961, 1.0 ]
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-14",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 389.0, 199.0, 74.0, 23.0 ],
									"style" : "",
									"text" : "clock binky"
								}

							}
, 							{
								"box" : 								{
									"bubble" : 1,
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-12",
									"linecount" : 2,
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 502.0, 134.5, 98.0, 40.0 ],
									"style" : "",
									"text" : "Sequencing interval (ms)"
								}

							}
, 							{
								"box" : 								{
									"attr" : "playstep",
									"id" : "obj-11",
									"maxclass" : "attrui",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 341.0, 143.0, 150.0, 23.0 ],
									"style" : ""
								}

							}
, 							{
								"box" : 								{
									"bubble" : 1,
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-9",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 162.0, 143.0, 163.0, 25.0 ],
									"style" : "",
									"text" : "Start/stop sequencing"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-8",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 113.0, 143.0, 35.0, 23.0 ],
									"style" : "",
									"text" : "stop"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-7",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 73.0, 143.0, 34.0, 23.0 ],
									"style" : "",
									"text" : "play"
								}

							}
, 							{
								"box" : 								{
									"bubble" : 1,
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-5",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 73.0, 112.0, 163.0, 25.0 ],
									"style" : "",
									"text" : "Perform single time tick"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-4",
									"maxclass" : "button",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "bang" ],
									"patching_rect" : [ 44.0, 112.0, 24.0, 24.0 ],
									"style" : ""
								}

							}
, 							{
								"box" : 								{
									"bubble" : 1,
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-17",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 57.0, 83.0, 128.0, 25.0 ],
									"style" : "",
									"text" : "Send all note-offs"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-6",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 15.0, 83.0, 38.0, 23.0 ],
									"style" : "",
									"text" : "flush"
								}

							}
, 							{
								"box" : 								{
									"bounce_data_0000000000" : [ "bounce", "(", "room", "(", "vertices", "(", "(", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1078325780, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1077441825, ")", "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1085763584, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", "(", "(", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3225689098, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079714903, ")", "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1085763584, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", "(", "(", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3227456788, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1077441825, ")", "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1085763584, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", "(", "(", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3225689098, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3226325901, ")", "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1085763584, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", "(", "(", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079991265, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3225564432, ")", "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1085763584, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", "(", "(", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1078502265, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079056934, ")", "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1085763584, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", "(", "(", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3226631370, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1077698213, ")", "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1085763584, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", "(", "(", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3226631370, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3227077817, ")", "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1085763584, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", "(", "(", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1078502265, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3227625371, ")", "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1085763584, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", ")", "(", "edges", "(", 1, 2, "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1085763584, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", "(", 2, 3, "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1086070784, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", "(", 3, 4, "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1086250484, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", "(", 4, 1, "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1086351360, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", "(", 5, 6, "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1085763584, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", "(", 6, 7, "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1086070784, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", "(", 7, 8, "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1086250484, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", "(", 8, 9, "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1086351360, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", "(", 9, 5, "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1086400808, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", ")", ")", "(", "balls", "(", "(", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3225602112, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1071901832, ")", "(", "speed", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1077864189, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3226977983, ")", "(", "color", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1071225241, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, ")", "(", "channel", 1, ")", "(", "flags", ")", ")", "(", "(", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1077937467, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3226664497, ")", "(", "speed", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1078535965, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3227500607, ")", "(", "color", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1071225241, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, ")", "(", "channel", 1, ")", "(", "flags", ")", ")", ")" ],
									"bounce_data_count" : [ 1 ],
									"id" : "obj-1",
									"maxclass" : "dada.bounce",
									"numinlets" : 2,
									"numoutlets" : 5,
									"out" : "nnnn",
									"outlettype" : [ "", "", "", "", "bang" ],
									"patching_rect" : [ 15.0, 189.0, 290.0, 289.0 ],
									"versionnumber" : 10000,
									"zoom" : 91.996155
								}

							}
, 							{
								"box" : 								{
									"border" : 0,
									"filename" : "helpname.js",
									"id" : "obj-2",
									"ignoreclick" : 1,
									"jsarguments" : [ "dada.bounce" ],
									"maxclass" : "jsui",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 10.0, 10.0, 273.295868, 57.567627 ]
								}

							}
 ],
						"lines" : [ 							{
								"patchline" : 								{
									"destination" : [ "obj-13", 0 ],
									"source" : [ "obj-1", 3 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-1", 0 ],
									"source" : [ "obj-11", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-1", 0 ],
									"source" : [ "obj-14", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-1", 0 ],
									"source" : [ "obj-15", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-10", 0 ],
									"midpoints" : [ 391.5, 473.0, 391.5, 473.0 ],
									"source" : [ "obj-18", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-18", 0 ],
									"source" : [ "obj-19", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-1", 0 ],
									"source" : [ "obj-23", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-1", 0 ],
									"source" : [ "obj-26", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-1", 0 ],
									"source" : [ "obj-4", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-1", 0 ],
									"source" : [ "obj-6", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-1", 0 ],
									"source" : [ "obj-7", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-1", 0 ],
									"source" : [ "obj-8", 0 ]
								}

							}
 ]
					}
,
					"patching_rect" : [ 89.0, 264.0, 68.0, 22.0 ],
					"saved_object_attributes" : 					{
						"description" : "",
						"digest" : "",
						"fontsize" : 13.0,
						"globalpatchername" : "",
						"style" : "",
						"tags" : ""
					}
,
					"style" : "",
					"text" : "p playback",
					"varname" : "basic_tab[4]"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"id" : "obj-5",
					"maxclass" : "newobj",
					"numinlets" : 0,
					"numoutlets" : 0,
					"patcher" : 					{
						"fileversion" : 1,
						"appversion" : 						{
							"major" : 7,
							"minor" : 3,
							"revision" : 4,
							"architecture" : "x64",
							"modernui" : 1
						}
,
						"rect" : [ 0.0, 26.0, 703.0, 533.0 ],
						"bglocked" : 0,
						"openinpresentation" : 0,
						"default_fontsize" : 13.0,
						"default_fontface" : 0,
						"default_fontname" : "Arial",
						"gridonopen" : 1,
						"gridsize" : [ 5.0, 5.0 ],
						"gridsnaponopen" : 1,
						"objectsnaponopen" : 1,
						"statusbarvisible" : 2,
						"toolbarvisible" : 1,
						"lefttoolbarpinned" : 0,
						"toptoolbarpinned" : 0,
						"righttoolbarpinned" : 0,
						"bottomtoolbarpinned" : 0,
						"toolbars_unpinned_last_save" : 0,
						"tallnewobj" : 0,
						"boxanimatetime" : 200,
						"enablehscroll" : 1,
						"enablevscroll" : 1,
						"devicewidth" : 0.0,
						"description" : "",
						"digest" : "",
						"tags" : "",
						"style" : "",
						"subpatcher_template" : "",
						"showontab" : 1,
						"boxes" : [ 							{
								"box" : 								{
									"id" : "obj-27",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 311.0, 441.0, 146.0, 23.0 ],
									"style" : "",
									"text" : "rotate component 2 60°"
								}

							}
, 							{
								"box" : 								{
									"bubble" : 1,
									"id" : "obj-26",
									"linecount" : 3,
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 588.0, 400.5, 94.0, 54.0 ],
									"style" : "",
									"text" : "Rotate (in radians or degrees)"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-25",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 453.0, 416.0, 102.0, 23.0 ],
									"style" : "",
									"text" : "rotate ball 2 30°"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-24",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 311.0, 416.0, 129.0, 23.0 ],
									"style" : "",
									"text" : "rotate ball 2 3.14159"
								}

							}
, 							{
								"box" : 								{
									"bubble" : 1,
									"id" : "obj-23",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 420.0, 382.0, 207.0, 25.0 ],
									"style" : "",
									"text" : "Multiply velocity of ball 2 by 0.5"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-22",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 311.0, 382.0, 97.0, 23.0 ],
									"style" : "",
									"text" : "scale ball 2 0.5"
								}

							}
, 							{
								"box" : 								{
									"bubble" : 1,
									"id" : "obj-21",
									"linecount" : 2,
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 471.0, 340.5, 157.0, 40.0 ],
									"style" : "",
									"text" : "Scale first component by a factor of 1.01"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-20",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 311.0, 349.0, 149.0, 23.0 ],
									"style" : "",
									"text" : "scale component 1 1.02"
								}

							}
, 							{
								"box" : 								{
									"bubble" : 1,
									"bubblepoint" : 0.7,
									"id" : "obj-15",
									"linecount" : 3,
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 228.0, 471.0, 308.0, 54.0 ],
									"style" : "",
									"text" : "Sometimes it is useful to recover the indices of the split/subdivided elements; they are output as notifications in human-readable form"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-3",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 80.5, 497.0, 136.0, 23.0 ],
									"saved_object_attributes" : 									{
										"versionnumber" : 80001
									}
,
									"style" : "",
									"text" : "bach.print Notification"
								}

							}
, 							{
								"box" : 								{
									"bubble" : 1,
									"id" : "obj-18",
									"linecount" : 4,
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 522.0, 271.0, 151.0, 69.0 ],
									"style" : "",
									"text" : "Set meta-information for 4th vertex (if meta-information is vertex-assigned)"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-19",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 311.0, 294.0, 208.0, 23.0 ],
									"style" : "",
									"text" : "meta vertex 4 (pitch 6200) (vel 80)"
								}

							}
, 							{
								"box" : 								{
									"bubble" : 1,
									"id" : "obj-17",
									"linecount" : 2,
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 522.0, 220.5, 151.0, 40.0 ],
									"style" : "",
									"text" : "Set meta-information for 5th edge"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-16",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 311.0, 229.0, 202.0, 23.0 ],
									"style" : "",
									"text" : "meta edge 5 (pitch 6300) (vel 80)"
								}

							}
, 							{
								"box" : 								{
									"bubble" : 1,
									"id" : "obj-14",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 326.0, 190.0, 207.0, 25.0 ],
									"style" : "",
									"text" : "Subdivide 5th edge into 4 parts"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-13",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 200.0, 192.0, 120.0, 23.0 ],
									"style" : "",
									"text" : "subdivide edge 5 4"
								}

							}
, 							{
								"box" : 								{
									"bubble" : 1,
									"id" : "obj-12",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 307.0, 163.0, 270.0, 25.0 ],
									"style" : "",
									"text" : "Split 3rd edge by adding a point at (-40, 0)"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-11",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 183.0, 163.0, 119.0, 23.0 ],
									"style" : "",
									"text" : "split edge 3 (-40 0)"
								}

							}
, 							{
								"box" : 								{
									"bubble" : 1,
									"id" : "obj-10",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 200.0, 128.0, 197.0, 25.0 ],
									"style" : "",
									"text" : "Shift 2nd edge up by 10"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-8",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 68.0, 128.0, 123.0, 23.0 ],
									"style" : "",
									"text" : "move edge 3 (0 10)"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-9",
									"linecount" : 3,
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 412.0, 109.0, 225.0, 50.0 ],
									"style" : "",
									"text" : "Indices of elements are usually retrievable also at hit time (see the \"hitting\" tab)",
									"textcolor" : [ 0.501961, 0.501961, 0.501961, 1.0 ]
								}

							}
, 							{
								"box" : 								{
									"bubble" : 1,
									"id" : "obj-7",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 183.0, 99.0, 197.0, 25.0 ],
									"style" : "",
									"text" : "Move the 5th vertex by (-4, 0)"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-6",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 48.0, 101.0, 127.0, 23.0 ],
									"style" : "",
									"text" : "move vertex 5 (-4 0)"
								}

							}
, 							{
								"box" : 								{
									"bubble" : 1,
									"id" : "obj-5",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 192.0, 76.0, 364.0, 25.0 ],
									"style" : "",
									"text" : "Move the first connected component by the (10, 10) vector"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-4",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 15.0, 76.0, 166.0, 23.0 ],
									"style" : "",
									"text" : "move component 1 (10 10)"
								}

							}
, 							{
								"box" : 								{
									"bounce_data_0000000000" : [ "bounce", "(", "room", "(", "vertices", "(", "(", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1078681900, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1078080715, ")", "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1085763584, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", "(", "(", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3225246178, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079910772, ")", "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1085763584, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", "(", "(", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3227278727, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1078080715, ")", "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1085763584, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", "(", "(", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3225246178, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3225934161, ")", "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1085763584, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", "(", "(", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 2523293285, 3225678338, "_x_x_x_x_bach_float64_x_x_x_x_", 751619275, 1078822065, ")", "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1085763584, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", "(", "(", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 2872259378, 3226936786, "_x_x_x_x_bach_float64_x_x_x_x_", 3006477109, 3226315327, ")", "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1085763584, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", "(", "(", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 2576980400, 1074631628, "_x_x_x_x_bach_float64_x_x_x_x_", 3838627021, 3227664615, ")", "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1085763584, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", "(", "(", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 3570191566, 1079835143, "_x_x_x_x_bach_float64_x_x_x_x_", 2308544922, 3226750878, ")", "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1085763584, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", "(", "(", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 1422707918, 1079393779, "_x_x_x_x_bach_float64_x_x_x_x_", 3972844747, 1078378267, ")", "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1085763584, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", ")", "(", "edges", "(", 1, 2, "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1085763584, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", "(", 2, 3, "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1086070784, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", "(", 3, 4, "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1086250484, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", "(", 4, 1, "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1086351360, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", "(", 5, 6, "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1085840384, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", "(", 6, 7, "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1086070784, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", "(", 7, 8, "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1086250484, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", "(", 8, 9, "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1086351360, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", "(", 9, 5, "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1086400808, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", ")", ")", "(", "balls", "(", "(", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 3223832383, "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1078054049, ")", "(", "speed", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3226745268, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1078813607, ")", "(", "color", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1071225241, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, ")", "(", "channel", 1, ")", "(", "flags", ")", ")", "(", "(", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1079182193, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1075270311, ")", "(", "speed", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 3226618719, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079826025, ")", "(", "color", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1071225241, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, ")", "(", "channel", 1, ")", "(", "flags", ")", ")", ")" ],
									"bounce_data_count" : [ 1 ],
									"center" : [ -4.585789, 12.738304 ],
									"id" : "obj-1",
									"maxclass" : "dada.bounce",
									"numinlets" : 2,
									"numoutlets" : 5,
									"out" : "nnnn",
									"outlettype" : [ "", "", "", "", "bang" ],
									"patching_rect" : [ 15.0, 231.0, 281.0, 258.0 ],
									"showgrid" : 1,
									"versionnumber" : 10000,
									"zoom" : 91.996155
								}

							}
, 							{
								"box" : 								{
									"border" : 0,
									"filename" : "helpname.js",
									"id" : "obj-2",
									"ignoreclick" : 1,
									"jsarguments" : [ "dada.bounce" ],
									"maxclass" : "jsui",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 10.0, 10.0, 273.295868, 57.567627 ]
								}

							}
 ],
						"lines" : [ 							{
								"patchline" : 								{
									"destination" : [ "obj-3", 0 ],
									"source" : [ "obj-1", 1 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-1", 0 ],
									"source" : [ "obj-11", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-1", 0 ],
									"source" : [ "obj-13", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-1", 0 ],
									"source" : [ "obj-16", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-1", 0 ],
									"source" : [ "obj-19", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-1", 0 ],
									"source" : [ "obj-20", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-1", 0 ],
									"source" : [ "obj-22", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-1", 0 ],
									"source" : [ "obj-24", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-1", 0 ],
									"source" : [ "obj-25", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-1", 0 ],
									"source" : [ "obj-27", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-1", 0 ],
									"source" : [ "obj-4", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-1", 0 ],
									"source" : [ "obj-6", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-1", 0 ],
									"source" : [ "obj-8", 0 ]
								}

							}
 ]
					}
,
					"patching_rect" : [ 71.0, 224.0, 56.0, 22.0 ],
					"saved_object_attributes" : 					{
						"description" : "",
						"digest" : "",
						"fontsize" : 13.0,
						"globalpatchername" : "",
						"style" : "",
						"tags" : ""
					}
,
					"style" : "",
					"text" : "p modify",
					"varname" : "basic_tab[2]"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"id" : "obj-3",
					"maxclass" : "newobj",
					"numinlets" : 0,
					"numoutlets" : 0,
					"patcher" : 					{
						"fileversion" : 1,
						"appversion" : 						{
							"major" : 7,
							"minor" : 3,
							"revision" : 4,
							"architecture" : "x64",
							"modernui" : 1
						}
,
						"rect" : [ 0.0, 26.0, 703.0, 533.0 ],
						"bglocked" : 0,
						"openinpresentation" : 0,
						"default_fontsize" : 13.0,
						"default_fontface" : 0,
						"default_fontname" : "Arial",
						"gridonopen" : 1,
						"gridsize" : [ 5.0, 5.0 ],
						"gridsnaponopen" : 1,
						"objectsnaponopen" : 1,
						"statusbarvisible" : 2,
						"toolbarvisible" : 1,
						"lefttoolbarpinned" : 0,
						"toptoolbarpinned" : 0,
						"righttoolbarpinned" : 0,
						"bottomtoolbarpinned" : 0,
						"toolbars_unpinned_last_save" : 0,
						"tallnewobj" : 0,
						"boxanimatetime" : 200,
						"enablehscroll" : 1,
						"enablevscroll" : 1,
						"devicewidth" : 0.0,
						"description" : "",
						"digest" : "",
						"tags" : "",
						"style" : "",
						"subpatcher_template" : "",
						"showontab" : 1,
						"boxes" : [ 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-3",
									"linecount" : 6,
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 315.0, 132.0, 280.0, 94.0 ],
									"style" : "",
									"text" : "Two modes are available: either edges contain metadata (pitch and velocity), which is output when they are hit, or vertex do, and the output metadata when an edge is hit is then the appropriate interpolation between the edge vertices metadata",
									"textcolor" : [ 0.501961, 0.501961, 0.501961, 1.0 ]
								}

							}
, 							{
								"box" : 								{
									"attr" : "mode",
									"id" : "obj-7",
									"maxclass" : "attrui",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 315.0, 228.0, 276.0, 23.0 ],
									"style" : ""
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-9",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 10.0, 473.0, 622.0, 21.0 ],
									"style" : "",
									"text" : "You can use such information to produce any kind of operation, including feedback operations on the data.",
									"textcolor" : [ 0.501961, 0.501961, 0.501961, 1.0 ]
								}

							}
, 							{
								"box" : 								{
									"bubble" : 1,
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-6",
									"linecount" : 3,
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 302.0, 409.5, 329.0, 54.0 ],
									"style" : "",
									"text" : "All bounce data is sent out in human-readable form, with the ball number, position of the hit, speed at the hit moment, edge index, component index"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-5",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 145.5, 425.0, 143.0, 23.0 ],
									"saved_object_attributes" : 									{
										"versionnumber" : 80001
									}
,
									"style" : "",
									"text" : "bach.print BounceData"
								}

							}
, 							{
								"box" : 								{
									"bubble" : 1,
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-17",
									"linecount" : 2,
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 170.0, 77.5, 161.0, 40.0 ],
									"style" : "",
									"text" : "Output bounce data whenever a edge is hit"
								}

							}
, 							{
								"box" : 								{
									"attr" : "bouncedata",
									"id" : "obj-4",
									"maxclass" : "attrui",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 10.0, 86.0, 150.0, 23.0 ],
									"style" : ""
								}

							}
, 							{
								"box" : 								{
									"bounce_data_0000000000" : [ "bounce", "(", "room", "(", "vertices", "(", "(", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1080082950, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3221316700, ")", "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1085763584, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", "(", "(", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079295560, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079638681, ")", "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1085771264, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", "(", "(", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3225408320, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1080050627, ")", "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1085763584, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", "(", "(", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3227449530, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1078745540, ")", "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1085763584, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", "(", "(", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3227449530, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3226371663, ")", "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1085763584, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", "(", "(", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3225408320, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3227569893, ")", "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1085763584, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", "(", "(", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079295560, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3227193567, ")", "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1085763584, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", ")", "(", "edges", "(", 1, 2, "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1085763584, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", "(", 2, 3, "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1086070784, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", "(", 3, 4, "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1086250484, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", "(", 4, 5, "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1086351360, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", "(", 5, 6, "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1086400808, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", "(", 6, 7, "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1086441210, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", "(", 7, 1, "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1086475369, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", ")", ")", "(", "balls", "(", "(", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1078045471, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1078264878, ")", "(", "speed", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3227039875, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3224227573, ")", "(", "color", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1071225241, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, ")", "(", "channel", 1, ")", "(", "flags", ")", ")", "(", "(", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3224041027, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3224098642, ")", "(", "speed", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3225568340, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079461271, ")", "(", "color", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1071225241, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, ")", "(", "channel", 2, ")", "(", "flags", ")", ")", ")" ],
									"bounce_data_count" : [ 1 ],
									"id" : "obj-1",
									"maxclass" : "dada.bounce",
									"mode" : 1,
									"noteoff" : 0,
									"numinlets" : 2,
									"numoutlets" : 5,
									"out" : "nnnn",
									"outlettype" : [ "", "", "", "", "bang" ],
									"patching_rect" : [ 10.0, 126.0, 290.0, 289.0 ],
									"versionnumber" : 10000,
									"zoom" : 91.996155
								}

							}
, 							{
								"box" : 								{
									"border" : 0,
									"filename" : "helpname.js",
									"id" : "obj-2",
									"ignoreclick" : 1,
									"jsarguments" : [ "dada.bounce" ],
									"maxclass" : "jsui",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 10.0, 10.0, 273.295868, 57.567627 ]
								}

							}
 ],
						"lines" : [ 							{
								"patchline" : 								{
									"destination" : [ "obj-5", 0 ],
									"source" : [ "obj-1", 2 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-1", 0 ],
									"source" : [ "obj-4", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-1", 0 ],
									"source" : [ "obj-7", 0 ]
								}

							}
 ]
					}
,
					"patching_rect" : [ 50.0, 188.0, 53.0, 22.0 ],
					"saved_object_attributes" : 					{
						"description" : "",
						"digest" : "",
						"fontsize" : 13.0,
						"globalpatchername" : "",
						"style" : "",
						"tags" : ""
					}
,
					"style" : "",
					"text" : "p hitting",
					"varname" : "basic_tab[1]"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"id" : "obj-6",
					"maxclass" : "newobj",
					"numinlets" : 0,
					"numoutlets" : 0,
					"patcher" : 					{
						"fileversion" : 1,
						"appversion" : 						{
							"major" : 7,
							"minor" : 3,
							"revision" : 4,
							"architecture" : "x64",
							"modernui" : 1
						}
,
						"rect" : [ 0.0, 26.0, 703.0, 533.0 ],
						"bglocked" : 0,
						"openinpresentation" : 0,
						"default_fontsize" : 13.0,
						"default_fontface" : 0,
						"default_fontname" : "Arial",
						"gridonopen" : 1,
						"gridsize" : [ 5.0, 5.0 ],
						"gridsnaponopen" : 1,
						"objectsnaponopen" : 1,
						"statusbarvisible" : 2,
						"toolbarvisible" : 1,
						"lefttoolbarpinned" : 0,
						"toptoolbarpinned" : 0,
						"righttoolbarpinned" : 0,
						"bottomtoolbarpinned" : 0,
						"toolbars_unpinned_last_save" : 0,
						"tallnewobj" : 0,
						"boxanimatetime" : 200,
						"enablehscroll" : 1,
						"enablevscroll" : 1,
						"devicewidth" : 0.0,
						"description" : "",
						"digest" : "",
						"tags" : "",
						"style" : "",
						"subpatcher_template" : "",
						"showontab" : 1,
						"boxes" : [ 							{
								"box" : 								{
									"bubble" : 1,
									"id" : "obj-16",
									"linecount" : 2,
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 553.0, 23.567627, 113.0, 40.0 ],
									"style" : "",
									"text" : "Set or get domain/range"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-14",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 446.0, 16.567627, 99.0, 23.0 ],
									"style" : "",
									"text" : "range -200 200"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-15",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 329.0, 16.567627, 108.0, 23.0 ],
									"style" : "",
									"text" : "domain -180 180"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-12",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 79.5, 506.0, 94.0, 23.0 ],
									"saved_object_attributes" : 									{
										"versionnumber" : 80001
									}
,
									"style" : "",
									"text" : "bach.print Res"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-11",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 415.0, 44.567627, 62.0, 23.0 ],
									"style" : "",
									"text" : "getrange"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-9",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 329.0, 44.567627, 71.0, 23.0 ],
									"style" : "",
									"text" : "getdomain"
								}

							}
, 							{
								"box" : 								{
									"bubble" : 1,
									"id" : "obj-8",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 317.0, 505.0, 319.0, 25.0 ],
									"style" : "",
									"text" : "bang whenever the object is changed via interface"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-6",
									"maxclass" : "button",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "bang" ],
									"patching_rect" : [ 288.0, 505.0, 24.0, 24.0 ],
									"style" : ""
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-5",
									"linecount" : 11,
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 310.0, 81.0, 360.0, 166.0 ],
									"style" : "",
									"text" : "Click+drag to move elements; add Alt key to duplicate them.\n\nUse Cmd+click (mac) or Ctrl+click (win) to delete elements (edges, vertices, shapes, balls).\n\nUse right click contextual menu on balls to mute/solo them, to make them inactive (i.e. they won't move at all) change their speed direction, their midichannel, their color.\n\nUse right click contextual menu anywhere else to add balls or room elements.",
									"textcolor" : [ 0.501961, 0.0, 0.0, 1.0 ]
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-4",
									"linecount" : 17,
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 310.0, 247.567627, 341.0, 253.0 ],
									"style" : "",
									"text" : "Key-mapped tools (hold down key while them mouse is on the appropriate element, and the pointer will changed to desired tool):\n\nS: scale (balls velocity, or room elements)\nR: rotate (balls velocity or room elements)\nN: change element pitch (vertices, edges, shapes)\nV: change element velocity(vertices, edges, shapes)\nQ: change ball color\nL: add edge by gluing vertices together\n\nScroll the mouse to move the region\nCmd+Scroll (mac) or Ctrl+Scroll (win) to change zoom\nEsc to re-center\nTab to autozoom\nCmd+Z (mac) or Ctrl+Z (win) to undo\nCmd+Shift+Z (mac) or Ctrl+Y (win) to redo",
									"textcolor" : [ 0.501961, 0.0, 0.0, 1.0 ]
								}

							}
, 							{
								"box" : 								{
									"bounce_data_0000000000" : [ "bounce", "(", "room", "(", "vertices", "(", "(", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3227271889, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1075167674, ")", "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1085763584, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", "(", "(", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3226009804, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1075167674, ")", "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1085763584, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", "(", "(", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079360814, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1080667661, ")", "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1085763584, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", "(", "(", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3227271889, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1080667661, ")", "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1085763584, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", "(", "(", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1076428868, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3225867192, ")", "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1085763584, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", "(", "(", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1077548406, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079117510, ")", "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1085763584, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", "(", "(", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1077548406, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1080121528, ")", "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1085763584, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", "(", "(", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079360814, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1080121528, ")", "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1085763584, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", "(", "(", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1080126866, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3227671762, ")", "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1085873664, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", "(", "(", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079690357, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3226800007, ")", "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1085873664, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", "(", "(", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3227548346, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3226513994, ")", "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1085873664, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", "(", "(", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3223391590, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3228089011, ")", "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1085873664, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", "(", "(", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1078550148, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3227441291, ")", "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1085873664, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", "(", "(", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1085873664, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", "(", "(", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3226515056, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3226755483, ")", "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1085873664, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", "(", "(", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3226817817, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3226541770, ")", "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1085873664, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", ")", "(", "edges", "(", 1, 2, "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1085763584, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", "(", 2, 5, "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1086173184, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", "(", 3, 4, "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1086250484, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", "(", 4, 1, "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1085763584, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", "(", 5, 6, "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1086070784, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", "(", 6, 7, "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1086239744, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", "(", 7, 8, "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", ")", "(", 8, 3, "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1086324224, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", "(", 9, 10, "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1085873664, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", "(", 10, 13, "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1086283264, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", "(", 11, 12, "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1086342650, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", "(", 12, 9, "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1085873664, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", "(", 15, 16, "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1086180864, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", "(", 16, 11, "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1086379520, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", "(", 14, 6, "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1085763584, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", "(", 14, 13, "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1085763584, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", ")", ")", "(", "balls", "(", "(", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3226251729, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079467739, ")", "(", "speed", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3227058176, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1024168859, ")", "(", "color", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1071225241, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, ")", "(", "channel", 1, ")", "(", "flags", ")", ")", "(", "(", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3226639722, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1080320411, ")", "(", "speed", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3227058176, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1024168860, ")", "(", "color", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1071225241, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, ")", "(", "channel", 2, ")", "(", "flags", ")", ")", "(", "(", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3225457575, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079770500, ")", "(", "speed", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1003293730, ")", "(", "color", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1071225241, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, ")", "(", "channel", 3, ")", "(", "flags", ")", ")", "(", "(", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3224711760, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3227563632, ")", "(", "speed", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1003293730, ")", "(", "color", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072064102, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072022159, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, ")", "(", "channel", 4, ")", "(", "flags", ")", ")", "(", "(", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3224054991, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3227343195, ")", "(", "speed", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1003293730, ")", "(", "color", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072001187, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1071393013, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, ")", "(", "channel", 5, ")", "(", "flags", ")", ")", "(", "(", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3226431529, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3227503480, ")", "(", "speed", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1003293730, ")", "(", "color", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1071225241, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1071225241, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, ")", "(", "channel", 6, ")", "(", "flags", ")", ")", "(", "(", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1078175397, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3224676141, ")", "(", "speed", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1003293730, ")", "(", "color", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1071225241, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, ")", "(", "channel", 7, ")", "(", "flags", ")", ")", ")" ],
									"bounce_data_count" : [ 1 ],
									"bouncedata" : 0,
									"id" : "obj-1",
									"maxclass" : "dada.bounce",
									"numinlets" : 2,
									"numoutlets" : 5,
									"out" : "nnnn",
									"outlettype" : [ "", "", "", "", "bang" ],
									"patching_rect" : [ 10.0, 81.0, 297.0, 417.0 ],
									"versionnumber" : 10000,
									"zoom" : 91.996155
								}

							}
, 							{
								"box" : 								{
									"border" : 0,
									"filename" : "helpname.js",
									"id" : "obj-2",
									"ignoreclick" : 1,
									"jsarguments" : [ "dada.bounce" ],
									"maxclass" : "jsui",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 10.0, 10.0, 273.295868, 57.567627 ]
								}

							}
 ],
						"lines" : [ 							{
								"patchline" : 								{
									"destination" : [ "obj-12", 0 ],
									"source" : [ "obj-1", 1 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-6", 0 ],
									"source" : [ "obj-1", 4 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-1", 0 ],
									"midpoints" : [ 424.5, 73.783813, 19.5, 73.783813 ],
									"source" : [ "obj-11", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-1", 0 ],
									"midpoints" : [ 455.5, 74.783813, 19.5, 74.783813 ],
									"source" : [ "obj-14", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-1", 0 ],
									"midpoints" : [ 338.5, 74.783813, 19.5, 74.783813 ],
									"source" : [ "obj-15", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-1", 0 ],
									"midpoints" : [ 338.5, 73.783813, 19.5, 73.783813 ],
									"source" : [ "obj-9", 0 ]
								}

							}
 ]
					}
,
					"patching_rect" : [ 22.0, 119.0, 67.0, 22.0 ],
					"saved_object_attributes" : 					{
						"description" : "",
						"digest" : "",
						"fontsize" : 13.0,
						"globalpatchername" : "",
						"style" : "",
						"tags" : ""
					}
,
					"style" : "",
					"text" : "p interface",
					"varname" : "basic_tab[3]"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"id" : "obj-1",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 300.0, 205.0, 163.0, 22.0 ],
					"saved_object_attributes" : 					{
						"filename" : "helpstarter.js",
						"parameter_enable" : 0
					}
,
					"style" : "",
					"text" : "js helpstarter.js dada.bounce"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"id" : "obj-2",
					"maxclass" : "newobj",
					"numinlets" : 0,
					"numoutlets" : 0,
					"patcher" : 					{
						"fileversion" : 1,
						"appversion" : 						{
							"major" : 7,
							"minor" : 3,
							"revision" : 4,
							"architecture" : "x64",
							"modernui" : 1
						}
,
						"rect" : [ 0.0, 26.0, 703.0, 533.0 ],
						"bglocked" : 0,
						"openinpresentation" : 0,
						"default_fontsize" : 13.0,
						"default_fontface" : 0,
						"default_fontname" : "Arial",
						"gridonopen" : 1,
						"gridsize" : [ 5.0, 5.0 ],
						"gridsnaponopen" : 1,
						"objectsnaponopen" : 1,
						"statusbarvisible" : 2,
						"toolbarvisible" : 1,
						"lefttoolbarpinned" : 0,
						"toptoolbarpinned" : 0,
						"righttoolbarpinned" : 0,
						"bottomtoolbarpinned" : 0,
						"toolbars_unpinned_last_save" : 0,
						"tallnewobj" : 0,
						"boxanimatetime" : 200,
						"enablehscroll" : 1,
						"enablevscroll" : 1,
						"devicewidth" : 0.0,
						"description" : "",
						"digest" : "",
						"tags" : "",
						"style" : "",
						"subpatcher_template" : "",
						"showontab" : 1,
						"boxes" : [ 							{
								"box" : 								{
									"id" : "obj-25",
									"maxclass" : "preset",
									"numinlets" : 1,
									"numoutlets" : 4,
									"outlettype" : [ "preset", "int", "preset", "int" ],
									"patching_rect" : [ 307.0, 186.5, 17.0, 59.5 ],
									"preset_data" : [ 										{
											"number" : 1,
											"data" : [ 5, "obj-1", "dada.bounce", "begin_preset", 453, 256, "obj-1", "dada.bounce", "restore_preset", 0, 250, "setstoredstate", "(", "room", "(", "(", "vertices", "(", "(", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3227058176, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3227058176, ")", "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1085763584, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", "(", "(", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 38348, 3225582378, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3227058176, ")", "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1085763584, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", "(", "(", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1085763584, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", "(", "(", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3227058176, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1085763584, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", "(", "(", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 38348, 3225582378, "_x_x_x_x_bach_float64_x_x_x_x_", 43692, 3225463466, ")", "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1085763584, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", "(", "(", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 4800, 1078169694, "_x_x_x_x_bach_float64_x_x_x_x_", 43692, 3225463466, ")", "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1085763584, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", "(", "(", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 4800, 1078169694, "_x_x_x_x_bach_float64_x_x_x_x_", 43688, 1077979818, ")", "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1085763584, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", "(", "(", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, "_x_x_x_x_bach_float64_x_x_x_x_", 43688, 1077979818, ")", "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1085763584, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", ")", "(", "edges", "(", 1, 2, "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1085763584, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", "(", 2, 5, "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1086173184, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", "(", 3, 4, "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 52350, 1086250484, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", "(", 4, 1, "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1085763584, ")", 209, "obj-1", "dada.bounce", "restore_preset", 250, 203, "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", "(", 5, 6, "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1086070784, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", "(", 6, 7, "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1086239744, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", "(", 7, 8, "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1086070784, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", "(", 8, 3, "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1086324224, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", ")", ")", ")", "(", "balls", "(", "(", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 48384, 3226028618, "_x_x_x_x_bach_float64_x_x_x_x_", 2626, 1028704530, ")", "(", "speed", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3147880640, ")", "(", "color", "_x_x_x_x_bach_float64_x_x_x_x_", 39322, 1071225241, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, ")", "(", "channel", 1, ")", "(", "flags", ")", ")", "(", "(", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 61508, 3226735862, "_x_x_x_x_bach_float64_x_x_x_x_", 58737, 1079058122, ")", "(", "speed", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3227058176, "_x_x_x_x_bach_float64_x_x_x_x_", 25044, 1024168860, ")", "(", "color", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 39322, 1071225241, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, ")", "(", "channel", 2, ")", "(", "flags", ")", ")", "(", "(", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 9786, 3226302452, "_x_x_x_x_bach_float64_x_x_x_x_", 61250, 3226470532, ")", "(", "speed", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3227058176, "_x_x_x_x_bach_float64_x_x_x_x_", 62384, 1024168861, ")", "(", "color", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 39322, 1071225241, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, ")", "(", "channel", 3, ")", "(", "flags", ")", ")", ")", 4, "obj-1", "dada.bounce", "end_preset", 5, "obj-7", "dada.bounce", "begin_preset", 560, 256, "obj-7", "dada.bounce", "restore_preset", 0, 250, "setstoredstate", "(", "room", "(", "(", "vertices", "(", "(", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 42365, 1079250243, "_x_x_x_x_bach_float64_x_x_x_x_", 4315, 1079952360, ")", "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1085763584, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", "(", "(", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 20324, 3227427103, "_x_x_x_x_bach_float64_x_x_x_x_", 39507, 1079383813, ")", "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1085763584, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", "(", "(", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 55513, 3226858556, "_x_x_x_x_bach_float64_x_x_x_x_", 23179, 3227293533, ")", "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1085763584, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", "(", "(", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 7173, 1079818790, "_x_x_x_x_bach_float64_x_x_x_x_", 58371, 3226724986, ")", "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1085763584, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", "(", "(", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 10527, 1079031408, "_x_x_x_x_bach_float64_x_x_x_x_", 15292, 3224747379, ")", "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1085912064, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", "(", "(", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 46938, 3224197467, "_x_x_x_x_bach_float64_x_x_x_x_", 36721, 1077498906, ")", "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1085912064, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", "(", "(", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 49946, 3225742526, "_x_x_x_x_bach_float64_x_x_x_x_", 40366, 3224747379, ")", "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1085912064, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", "(", "(", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 30324, 3224197467, "_x_x_x_x_bach_float64_x_x_x_x_", 39478, 3226547136, ")", "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1085912064, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", "(", "(", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 34072, 1078187641, "_x_x_x_x_bach_float64_x_x_x_x_", 46460, 3226547136, ")", "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1085912064, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", ")", "(", "edges", "(", 1, 2, "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1085763584, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", "(", 2, 3, "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1086070784, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", "(", 3, 256, "obj-7", "dada.bounce", "restore_preset", 250, 250, 4, "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 52350, 1086250484, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", "(", 4, 1, "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1086351360, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", "(", 6, 7, "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 58943, 1086361850, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", "(", 7, 8, "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1086425600, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", "(", 8, 9, "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 41698, 1086475048, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", "(", 9, 5, "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 58943, 1086515450, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", ")", ")", ")", "(", "balls", "(", "(", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 32572, 1077874297, "_x_x_x_x_bach_float64_x_x_x_x_", 42366, 1078823609, ")", "(", "speed", "_x_x_x_x_bach_float64_x_x_x_x_", 726, 3226009602, "_x_x_x_x_bach_float64_x_x_x_x_", 7494, 3226838671, ")", "(", "color", "_x_x_x_x_bach_float64_x_x_x_x_", 39322, 1071225241, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, ")", "(", "channel", 1, ")", "(", "flags", ")", ")", "(", "(", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 2973, 3226492001, "_x_x_x_x_bach_float64_x_x_x_x_", 14971, 1079213122, ")", "(", "speed", "_x_x_x_x_bach_float64_x_x_x_x_", 5932, 1078525952, "_x_x_x_x_bach_float64_x_x_x_x_", 49261, 1079355023, ")", "(", "color", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 39322, 1071225241, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, ")", "(", "channel", 2, ")", "(", "flags", ")", ")", "(", "(", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 12196, 3226514244, "_x_x_x_x_bach_float64_x_x_x_x_", 49177, 3226117644, ")", "(", "speed", "_x_x_x_x_bach_float64_x_x_x_x_", 16306, 1080283989, "_x_x_x_x_bach_float64_x_x_x_x_", 12963, 3226204155, ")", "(", "color", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 39322, 1071225241, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, ")", "(", "channel", 3, ")", "(", "flags", ")", ")", "(", "(", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 61886, 1079222532, "_x_x_x_x_bach_float64_x_x_x_x_", 24651, 3226050190, ")", "(", "speed", "_x_x_x_x_bach_float64_x_x_x_x_", 45011, 1079464201, "_x_x_x_x_bach_float64_x_x_x_x_", 47530, 1078069660, ")", "(", "color", "_x_x_x_x_bach_float64_x_x_x_x_", 26214, 1072064102, "_x_x_x_x_bach_float64_x_x_x_x_", 66, "obj-7", "dada.bounce", "restore_preset", 500, 60, 62915, 1072022159, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, ")", "(", "channel", 4, ")", "(", "flags", ")", ")", "(", "(", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 50964, 1077263420, "_x_x_x_x_bach_float64_x_x_x_x_", 43023, 3222529690, ")", "(", "speed", "_x_x_x_x_bach_float64_x_x_x_x_", 10508, 1080252734, "_x_x_x_x_bach_float64_x_x_x_x_", 53693, 1079327032, ")", "(", "color", "_x_x_x_x_bach_float64_x_x_x_x_", 15729, 1072001187, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 23593, 1071393013, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, ")", "(", "channel", 5, ")", "(", "flags", ")", ")", ")", 4, "obj-7", "dada.bounce", "end_preset" ]
										}
, 										{
											"number" : 2,
											"data" : [ 5, "obj-1", "dada.bounce", "begin_preset", 453, 256, "obj-1", "dada.bounce", "restore_preset", 0, 250, "setstoredstate", "(", "room", "(", "(", "vertices", "(", "(", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3227058176, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3227058176, ")", "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1085763584, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", "(", "(", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 38348, 3225582378, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3227058176, ")", "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1085763584, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", "(", "(", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1085763584, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", "(", "(", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3227058176, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1085763584, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", "(", "(", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 38348, 3225582378, "_x_x_x_x_bach_float64_x_x_x_x_", 43692, 3225463466, ")", "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1085763584, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", "(", "(", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 4800, 1078169694, "_x_x_x_x_bach_float64_x_x_x_x_", 43692, 3225463466, ")", "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1085763584, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", "(", "(", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 4800, 1078169694, "_x_x_x_x_bach_float64_x_x_x_x_", 43688, 1077979818, ")", "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1085763584, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", "(", "(", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, "_x_x_x_x_bach_float64_x_x_x_x_", 43688, 1077979818, ")", "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1085763584, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", ")", "(", "edges", "(", 1, 2, "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1085763584, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", "(", 2, 5, "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1086173184, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", "(", 3, 4, "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 52350, 1086250484, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", "(", 4, 1, "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1085763584, ")", 209, "obj-1", "dada.bounce", "restore_preset", 250, 203, "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", "(", 5, 6, "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1086070784, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", "(", 6, 7, "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1086239744, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", "(", 7, 8, "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1086070784, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", "(", 8, 3, "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1086324224, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", ")", ")", ")", "(", "balls", "(", "(", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 48384, 3226028618, "_x_x_x_x_bach_float64_x_x_x_x_", 2626, 1028704530, ")", "(", "speed", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3147880640, ")", "(", "color", "_x_x_x_x_bach_float64_x_x_x_x_", 39322, 1071225241, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, ")", "(", "channel", 1, ")", "(", "flags", ")", ")", "(", "(", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 61508, 3226735862, "_x_x_x_x_bach_float64_x_x_x_x_", 58737, 1079058122, ")", "(", "speed", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3227058176, "_x_x_x_x_bach_float64_x_x_x_x_", 25044, 1024168860, ")", "(", "color", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 39322, 1071225241, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, ")", "(", "channel", 2, ")", "(", "flags", ")", ")", "(", "(", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 9786, 3226302452, "_x_x_x_x_bach_float64_x_x_x_x_", 61250, 3226470532, ")", "(", "speed", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3227058176, "_x_x_x_x_bach_float64_x_x_x_x_", 62384, 1024168861, ")", "(", "color", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 39322, 1071225241, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, ")", "(", "channel", 3, ")", "(", "flags", ")", ")", ")", 4, "obj-1", "dada.bounce", "end_preset", 5, "obj-7", "dada.bounce", "begin_preset", 388, 256, "obj-7", "dada.bounce", "restore_preset", 0, 250, "setstoredstate", "(", "room", "(", "(", "vertices", "(", "(", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 10527, 1079031408, "_x_x_x_x_bach_float64_x_x_x_x_", 15292, 3224747379, ")", "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1085912064, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", "(", "(", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 46896, 3225885002, "_x_x_x_x_bach_float64_x_x_x_x_", 69, 1079182788, ")", "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1085912064, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", "(", "(", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 30994, 3227191815, "_x_x_x_x_bach_float64_x_x_x_x_", 69, 3226666436, ")", "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1085912064, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", "(", "(", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 48791, 3224197467, "_x_x_x_x_bach_float64_x_x_x_x_", 9442, 3224747379, ")", "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1085912064, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", "(", "(", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 34072, 1078187641, "_x_x_x_x_bach_float64_x_x_x_x_", 46460, 3226547136, ")", "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1085912064, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", "(", "(", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 13197, 3225991859, "_x_x_x_x_bach_float64_x_x_x_x_", 35663, 3226969197, ")", "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1085912064, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", "(", "(", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 30047, 3222792702, "_x_x_x_x_bach_float64_x_x_x_x_", 20709, 3227432242, ")", "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1085912064, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", ")", "(", "edges", "(", 2, 3, "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 58943, 1086361850, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", "(", 3, 4, "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1086425600, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", "(", 4, 5, "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 41698, 1086475048, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", "(", 5, 1, "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 58943, 1086515450, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", "(", 2, 1, "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1085763584, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", 144, "obj-7", "dada.bounce", "restore_preset", 250, 138, "(", 4, 6, "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1085763584, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", "(", 5, 7, "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1085763584, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", "(", 7, 3, "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1085763584, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", ")", ")", ")", "(", "balls", "(", "(", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 43140, 3224640522, "_x_x_x_x_bach_float64_x_x_x_x_", 3825, 3226862340, ")", "(", "speed", "_x_x_x_x_bach_float64_x_x_x_x_", 45011, 1079464201, "_x_x_x_x_bach_float64_x_x_x_x_", 47530, 1078069660, ")", "(", "color", "_x_x_x_x_bach_float64_x_x_x_x_", 26214, 1072064102, "_x_x_x_x_bach_float64_x_x_x_x_", 62915, 1072022159, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, ")", "(", "channel", 4, ")", "(", "flags", ")", ")", "(", "(", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 15058, 3225778145, "_x_x_x_x_bach_float64_x_x_x_x_", 33768, 3221316700, ")", "(", "speed", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3227645986, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3227098741, ")", "(", "color", "_x_x_x_x_bach_float64_x_x_x_x_", 39321, 1069128089, "_x_x_x_x_bach_float64_x_x_x_x_", 34985, 1066585479, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1013972992, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, ")", "(", "channel", 5, ")", "(", "flags", ")", ")", ")", 4, "obj-7", "dada.bounce", "end_preset" ]
										}
 ],
									"style" : ""
								}

							}
, 							{
								"box" : 								{
									"attr" : "snaptogrid",
									"id" : "obj-18",
									"maxclass" : "attrui",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 484.0, 138.0, 150.0, 23.0 ],
									"style" : ""
								}

							}
, 							{
								"box" : 								{
									"attr" : "showgrid",
									"id" : "obj-15",
									"maxclass" : "attrui",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 467.5, 113.0, 150.0, 23.0 ],
									"style" : ""
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-13",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 332.0, 143.0, 34.0, 23.0 ],
									"style" : "",
									"text" : "play"
								}

							}
, 							{
								"box" : 								{
									"bubble" : 1,
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-17",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 103.0, 143.0, 148.0, 25.0 ],
									"style" : "",
									"text" : "Toggle sequencing"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-3",
									"maxclass" : "newobj",
									"numinlets" : 3,
									"numoutlets" : 2,
									"outlettype" : [ "", "int" ],
									"patching_rect" : [ 513.5, 446.0, 104.0, 23.0 ],
									"style" : "",
									"text" : "bach.ezmidiplay"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-10",
									"maxclass" : "newobj",
									"numinlets" : 3,
									"numoutlets" : 2,
									"outlettype" : [ "", "int" ],
									"patching_rect" : [ 193.5, 446.0, 104.0, 23.0 ],
									"style" : "",
									"text" : "bach.ezmidiplay"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-8",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 380.0, 143.0, 35.0, 23.0 ],
									"style" : "",
									"text" : "stop"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-9",
									"linecount" : 3,
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 12.0, 474.0, 622.0, 50.0 ],
									"style" : "",
									"text" : "By default edges contain meta-information with a pitch and a velocity, which is output from the playout whenever a ball bounces on the edge (hover the mouse on edges to see such information). The MIDIchannel information is, on the other hand, associated to the ball.",
									"textcolor" : [ 0.501961, 0.501961, 0.501961, 1.0 ]
								}

							}
, 							{
								"box" : 								{
									"bounce_data_0000000000" : [ "bounce", "(", "room", "(", "vertices", "(", "(", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079250243, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079952360, ")", "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1085763584, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", "(", "(", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3227427103, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079383813, ")", "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1085763584, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", "(", "(", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3226858556, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3227293533, ")", "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1085763584, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", "(", "(", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079818790, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3226724986, ")", "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1085763584, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", "(", "(", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079031408, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3224747379, ")", "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1085912064, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", "(", "(", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3224197467, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1077498906, ")", "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1085912064, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", "(", "(", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3225742526, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3224747379, ")", "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1085912064, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", "(", "(", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3224197467, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3226547136, ")", "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1085912064, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", "(", "(", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1078187641, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3226547136, ")", "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1085912064, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", ")", "(", "edges", "(", 1, 2, "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1085763584, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", "(", 2, 3, "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1086070784, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", "(", 3, 4, "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1086250484, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", "(", 4, 1, "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1086351360, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", "(", 6, 7, "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1086361850, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", "(", 7, 8, "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1086425600, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", "(", 8, 9, "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1086475048, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", "(", 9, 5, "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1086515450, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", ")", ")", "(", "balls", "(", "(", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 3226215150, "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 3225562630, ")", "(", "speed", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1077041498, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079546709, ")", "(", "color", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1071225241, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, ")", "(", "channel", 1, ")", "(", "flags", ")", ")", "(", "(", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 3226352972, "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1078414728, ")", "(", "speed", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1079481246, "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1077977427, ")", "(", "color", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1071225241, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, ")", "(", "channel", 2, ")", "(", "flags", ")", ")", "(", "(", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1079405867, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 3226646856, ")", "(", "speed", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1080297152, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1078563742, ")", "(", "color", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1071225241, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, ")", "(", "channel", 3, ")", "(", "flags", ")", ")", "(", "(", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1079174601, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1075429745, ")", "(", "speed", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1079148080, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1079038633, ")", "(", "color", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072064102, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072022159, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, ")", "(", "channel", 4, ")", "(", "flags", ")", ")", "(", "(", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1079150890, "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 3225311725, ")", "(", "speed", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 3227895497, "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1077711799, ")", "(", "color", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072001187, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1071393013, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, ")", "(", "channel", 5, ")", "(", "flags", ")", ")", ")" ],
									"bounce_data_count" : [ 1 ],
									"bouncedata" : 0,
									"id" : "obj-7",
									"maxclass" : "dada.bounce",
									"numinlets" : 2,
									"numoutlets" : 5,
									"out" : "nnnn",
									"outlettype" : [ "", "", "", "", "bang" ],
									"patching_rect" : [ 332.0, 182.0, 261.0, 248.0 ],
									"presentation_rect" : [ 367.0, 206.0, 300.0, 300.0 ],
									"showgrid" : 1,
									"versionnumber" : 10000,
									"zoom" : 91.996155
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-6",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 60.0, 143.0, 35.0, 23.0 ],
									"style" : "",
									"text" : "stop"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-5",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 12.0, 143.0, 34.0, 23.0 ],
									"style" : "",
									"text" : "play"
								}

							}
, 							{
								"box" : 								{
									"bounce_data_0000000000" : [ "bounce", "(", "room", "(", "vertices", "(", "(", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3227058176, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3227058176, ")", "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1085763584, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", "(", "(", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3225582378, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3227058176, ")", "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1085763584, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", "(", "(", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1085763584, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", "(", "(", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3227058176, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1085763584, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", "(", "(", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3225582378, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3225463466, ")", "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1085763584, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", "(", "(", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1078169694, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3225463466, ")", "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1085763584, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", "(", "(", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1078169694, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1077979818, ")", "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1085763584, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", "(", "(", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1077979818, ")", "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1085763584, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", ")", "(", "edges", "(", 1, 2, "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1085763584, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", "(", 2, 5, "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1086173184, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", "(", 3, 4, "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1086250484, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", "(", 4, 1, "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1085763584, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", "(", 5, 6, "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1086070784, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", "(", 6, 7, "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1086239744, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", "(", 7, 8, "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1086070784, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", "(", 8, 3, "(", "pitch", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1086324224, ")", "(", "velocity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", ")", ")", "(", "balls", "(", "(", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3225971462, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1028783105, ")", "(", "speed", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3147595853, ")", "(", "color", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1071225241, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, ")", "(", "channel", 1, ")", "(", "flags", ")", ")", "(", "(", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1078187539, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079058122, ")", "(", "speed", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3227058176, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1024168860, ")", "(", "color", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1071225241, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, ")", "(", "channel", 2, ")", "(", "flags", ")", ")", "(", "(", "coord", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3226841678, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3226470532, ")", "(", "speed", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3227058176, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1024168861, ")", "(", "color", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1071225241, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, ")", "(", "channel", 3, ")", "(", "flags", ")", ")", ")" ],
									"bounce_data_count" : [ 1 ],
									"bouncedata" : 0,
									"id" : "obj-1",
									"maxclass" : "dada.bounce",
									"numinlets" : 2,
									"numoutlets" : 5,
									"out" : "nnnn",
									"outlettype" : [ "", "", "", "", "bang" ],
									"patching_rect" : [ 12.0, 182.0, 261.0, 248.0 ],
									"showgrid" : 1,
									"versionnumber" : 10000,
									"zoom" : 91.996155
								}

							}
, 							{
								"box" : 								{
									"border" : 0,
									"filename" : "helpdetails.js",
									"id" : "obj-2",
									"ignoreclick" : 1,
									"jsarguments" : [ "dada.bounce", 80 ],
									"maxclass" : "jsui",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 10.0, 10.0, 583.0, 112.0 ]
								}

							}
 ],
						"lines" : [ 							{
								"patchline" : 								{
									"destination" : [ "obj-10", 0 ],
									"source" : [ "obj-1", 3 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-7", 0 ],
									"source" : [ "obj-13", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-1", 0 ],
									"midpoints" : [ 477.0, 175.5, 21.5, 175.5 ],
									"order" : 1,
									"source" : [ "obj-15", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-7", 0 ],
									"midpoints" : [ 477.0, 175.5, 341.5, 175.5 ],
									"order" : 0,
									"source" : [ "obj-15", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-1", 0 ],
									"midpoints" : [ 493.5, 174.0, 21.5, 174.0 ],
									"order" : 1,
									"source" : [ "obj-18", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-7", 0 ],
									"midpoints" : [ 493.5, 175.0, 341.5, 175.0 ],
									"order" : 0,
									"source" : [ "obj-18", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-7", 0 ],
									"source" : [ "obj-25", 1 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-1", 0 ],
									"source" : [ "obj-5", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-1", 0 ],
									"source" : [ "obj-6", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-3", 0 ],
									"source" : [ "obj-7", 3 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-7", 0 ],
									"source" : [ "obj-8", 0 ]
								}

							}
 ]
					}
,
					"patching_rect" : [ 10.0, 85.0, 50.0, 22.0 ],
					"saved_object_attributes" : 					{
						"description" : "",
						"digest" : "",
						"fontsize" : 13.0,
						"globalpatchername" : "",
						"style" : "",
						"tags" : ""
					}
,
					"style" : "",
					"text" : "p basic",
					"varname" : "basic_tab"
				}

			}
, 			{
				"box" : 				{
					"border" : 0,
					"filename" : "helpname.js",
					"id" : "obj-4",
					"ignoreclick" : 1,
					"jsarguments" : [ "dada.bounce" ],
					"maxclass" : "jsui",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 10.0, 10.0, 273.295868, 57.567627 ]
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"id" : "obj-8",
					"maxclass" : "newobj",
					"numinlets" : 0,
					"numoutlets" : 0,
					"patcher" : 					{
						"fileversion" : 1,
						"appversion" : 						{
							"major" : 7,
							"minor" : 3,
							"revision" : 4,
							"architecture" : "x64",
							"modernui" : 1
						}
,
						"rect" : [ 0.0, 26.0, 703.0, 533.0 ],
						"bglocked" : 0,
						"openinpresentation" : 0,
						"default_fontsize" : 13.0,
						"default_fontface" : 0,
						"default_fontname" : "Arial",
						"gridonopen" : 1,
						"gridsize" : [ 5.0, 5.0 ],
						"gridsnaponopen" : 1,
						"objectsnaponopen" : 1,
						"statusbarvisible" : 2,
						"toolbarvisible" : 1,
						"lefttoolbarpinned" : 0,
						"toptoolbarpinned" : 0,
						"righttoolbarpinned" : 0,
						"bottomtoolbarpinned" : 0,
						"toolbars_unpinned_last_save" : 0,
						"tallnewobj" : 0,
						"boxanimatetime" : 200,
						"enablehscroll" : 1,
						"enablevscroll" : 1,
						"devicewidth" : 0.0,
						"description" : "",
						"digest" : "",
						"tags" : "",
						"style" : "",
						"subpatcher_template" : "",
						"showontab" : 1,
						"boxes" : [  ],
						"lines" : [  ]
					}
,
					"patching_rect" : [ 205.0, 205.0, 50.0, 22.0 ],
					"saved_object_attributes" : 					{
						"description" : "",
						"digest" : "",
						"fontsize" : 13.0,
						"globalpatchername" : "",
						"style" : "",
						"tags" : ""
					}
,
					"style" : "",
					"text" : "p ?",
					"varname" : "q_tab"
				}

			}
 ],
		"lines" : [  ],
		"dependency_cache" : [ 			{
				"name" : "helpname.js",
				"bootpath" : "C74:/help/resources",
				"type" : "TEXT",
				"implicit" : 1
			}
, 			{
				"name" : "helpdetails.js",
				"bootpath" : "C74:/help/resources",
				"type" : "TEXT",
				"implicit" : 1
			}
, 			{
				"name" : "bach.ezmidiplay.maxpat",
				"bootpath" : "~/Documents/Max 7/Packages/bach/patchers",
				"patcherrelativepath" : "../../bach/patchers",
				"type" : "JSON",
				"implicit" : 1
			}
, 			{
				"name" : "bach.gcd.maxpat",
				"bootpath" : "~/Documents/Max 7/Packages/bach/patchers",
				"patcherrelativepath" : "../../bach/patchers",
				"type" : "JSON",
				"implicit" : 1
			}
, 			{
				"name" : "bach.approx.maxpat",
				"bootpath" : "~/Documents/Max 7/Packages/bach/patchers",
				"patcherrelativepath" : "../../bach/patchers",
				"type" : "JSON",
				"implicit" : 1
			}
, 			{
				"name" : "bach.filter.maxpat",
				"bootpath" : "~/Documents/Max 7/Packages/bach/patchers",
				"patcherrelativepath" : "../../bach/patchers",
				"type" : "JSON",
				"implicit" : 1
			}
, 			{
				"name" : "helpstarter.js",
				"bootpath" : "C74:/help/resources",
				"type" : "TEXT",
				"implicit" : 1
			}
, 			{
				"name" : "bach.times.maxpat",
				"bootpath" : "~/Documents/Max 7/Packages/bach/patchers",
				"patcherrelativepath" : "../../bach/patchers",
				"type" : "JSON",
				"implicit" : 1
			}
, 			{
				"name" : "bach.prepend.maxpat",
				"bootpath" : "~/Documents/Max 7/Packages/bach/patchers",
				"patcherrelativepath" : "../../bach/patchers",
				"type" : "JSON",
				"implicit" : 1
			}
, 			{
				"name" : "dada.commons.maxpat",
				"bootpath" : "~/Documents/Max 7/Packages/dada/help",
				"patcherrelativepath" : ".",
				"type" : "JSON",
				"implicit" : 1
			}
, 			{
				"name" : "mydadastuff.png",
				"bootpath" : "/private/tmp",
				"patcherrelativepath" : "../../../../../../../private/tmp",
				"type" : "PNG ",
				"implicit" : 1
			}
, 			{
				"name" : "dada.bounce.mxo",
				"type" : "iLaX"
			}
, 			{
				"name" : "bach.playkeys.mxo",
				"type" : "iLaX"
			}
, 			{
				"name" : "bach.expr.mxo",
				"type" : "iLaX"
			}
, 			{
				"name" : "bach.length.mxo",
				"type" : "iLaX"
			}
, 			{
				"name" : "bach.iter.mxo",
				"type" : "iLaX"
			}
, 			{
				"name" : "bach.flat.mxo",
				"type" : "iLaX"
			}
, 			{
				"name" : "bach.pick.mxo",
				"type" : "iLaX"
			}
, 			{
				"name" : "bach.args.mxo",
				"type" : "iLaX"
			}
, 			{
				"name" : "bach.reg.mxo",
				"type" : "iLaX"
			}
, 			{
				"name" : "bach.print.mxo",
				"type" : "iLaX"
			}
, 			{
				"name" : "bach.keys.mxo",
				"type" : "iLaX"
			}
, 			{
				"name" : "bach.portal.mxo",
				"type" : "iLaX"
			}
, 			{
				"name" : "bach.gt.mxo",
				"type" : "iLaX"
			}
, 			{
				"name" : "bach.is.mxo",
				"type" : "iLaX"
			}
, 			{
				"name" : "bach.neq.mxo",
				"type" : "iLaX"
			}
, 			{
				"name" : "bach.eq.mxo",
				"type" : "iLaX"
			}
, 			{
				"name" : "bach.nth.mxo",
				"type" : "iLaX"
			}
, 			{
				"name" : "bach.slice.mxo",
				"type" : "iLaX"
			}
, 			{
				"name" : "bach.post.mxo",
				"type" : "iLaX"
			}
, 			{
				"name" : "bach.join.mxo",
				"type" : "iLaX"
			}
, 			{
				"name" : "bach.score.mxo",
				"type" : "iLaX"
			}
, 			{
				"name" : "bach.wrap.mxo",
				"type" : "iLaX"
			}
, 			{
				"name" : "dada.bodies.mxo",
				"type" : "iLaX"
			}
, 			{
				"name" : "dada.catart.mxo",
				"type" : "iLaX"
			}
, 			{
				"name" : "dada.base.mxo",
				"type" : "iLaX"
			}
, 			{
				"name" : "mira.multitouch.mxo",
				"type" : "iLaX"
			}
 ],
		"autosave" : 0
	}

}
