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
		"rect" : [ 100.0, 97.0, 976.0, 650.0 ],
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
						"rect" : [ 0.0, 26.0, 976.0, 624.0 ],
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
									"id" : "obj-13",
									"linecount" : 2,
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 660.0, 247.0, 80.0, 40.0 ],
									"style" : "",
									"text" : "Delete a swarm"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-12",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 558.0, 257.0, 95.0, 23.0 ],
									"style" : "",
									"text" : "deleteswarm 2"
								}

							}
, 							{
								"box" : 								{
									"bubble" : 1,
									"id" : "obj-10",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 94.0, 219.0, 75.0, 25.0 ],
									"style" : "",
									"text" : "Clear all"
								}

							}
, 							{
								"box" : 								{
									"bubble" : 1,
									"bubbleside" : 2,
									"id" : "obj-9",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 371.0, 38.0, 95.0, 40.0 ],
									"style" : "",
									"text" : "Add 2 swarms"
								}

							}
, 							{
								"box" : 								{
									"bubble" : 1,
									"id" : "obj-16",
									"linecount" : 3,
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 418.0, 163.0, 174.0, 54.0 ],
									"style" : "",
									"text" : "This swarm has no rules, and has speed 0, hence won't move!"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-8",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 10.0, 565.0, 190.0, 23.0 ],
									"style" : "",
									"text" : "bach.post Dump @maxdepth 2"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-7",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 560.0, 335.0, 91.0, 23.0 ],
									"style" : "",
									"text" : "dump swarms"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-6",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 560.0, 304.0, 43.0, 23.0 ],
									"style" : "",
									"text" : "dump"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-5",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 53.0, 219.0, 39.0, 23.0 ],
									"style" : "",
									"text" : "clear"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-1",
									"linecount" : 2,
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 33.0, 171.0, 375.0, 38.0 ],
									"style" : "",
									"text" : "addswarms ((size 30) (coord uniform 400 0 100 100) (speed 0 0) (color 0 0 0.3 1) (name steadyswarm))"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-34",
									"linecount" : 5,
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 10.0, 80.0, 738.0, 81.0 ],
									"style" : "",
									"text" : "addswarms ((size 200) (coord uniform 0 0 300 300) (speed uniform 0 0 10 10) (color 0.7 0 0 1) (name swarm1) (maxspeed 200) (applyrule center avoid align (wind (gain 0.5) (speed -20 -20)) (leftbarrier (position 0) (repulsion 20)) (rightbarrier (position 3000) (repulsion 20)) (topbarrier (position 1760) (repulsion 20)) (bottombarrier (position 0) (repulsion 1000)))) ((size 100) (coord uniform -180 -60 100 400) (speed uniform 0 0 20 0) (color 0. 0.3 0 1) (name swarm2) (maxspeed 200) (applyrule center avoid align (rightbarrier (position 180) (repulsion 30))))"
								}

							}
, 							{
								"box" : 								{
									"bgimage" : "sky.jpg",
									"boids_data_0000000000" : [ "boids", "(", "rules", ")", "(", "swarms", ")" ],
									"boids_data_count" : [ 1 ],
									"center" : [ -168.304734, -168.939589 ],
									"fontface" : 0,
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"id" : "obj-4",
									"maxclass" : "dada.boids",
									"numinlets" : 2,
									"numoutlets" : 4,
									"out" : "nn",
									"outlettype" : [ "", "", "list", "bang" ],
									"patching_rect" : [ 10.0, 247.0, 532.0, 303.0 ],
									"showaxes" : 1,
									"showgridlabels" : 1,
									"zoom" : 60.345843
								}

							}
, 							{
								"box" : 								{
									"border" : 0,
									"filename" : "helpname.js",
									"id" : "obj-2",
									"ignoreclick" : 1,
									"jsarguments" : [ "dada.boids" ],
									"maxclass" : "jsui",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 10.0, 10.0, 231.100128, 57.567627 ]
								}

							}
 ],
						"lines" : [ 							{
								"patchline" : 								{
									"destination" : [ "obj-4", 0 ],
									"source" : [ "obj-1", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-4", 0 ],
									"source" : [ "obj-12", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-4", 0 ],
									"source" : [ "obj-34", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-8", 0 ],
									"source" : [ "obj-4", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-4", 0 ],
									"source" : [ "obj-5", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-4", 0 ],
									"source" : [ "obj-6", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-4", 0 ],
									"source" : [ "obj-7", 0 ]
								}

							}
 ],
						"styles" : [ 							{
								"name" : "jpatcher001",
								"parentstyle" : "",
								"multi" : 0
							}
, 							{
								"name" : "preset001",
								"default" : 								{
									"accentcolor" : [ 0.5, 0.5, 0.5, 1.0 ]
								}
,
								"parentstyle" : "",
								"multi" : 0
							}
 ]
					}
,
					"patching_rect" : [ 59.0, 176.0, 87.0, 22.0 ],
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
					"text" : "p \"rule syntax\"",
					"varname" : "basic_tab[6]"
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
						"rect" : [ 0.0, 26.0, 976.0, 624.0 ],
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
									"id" : "obj-22",
									"linecount" : 3,
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 847.0, 404.0, 92.0, 54.0 ],
									"presentation_rect" : [ 789.0, 415.5, 0.0, 0.0 ],
									"style" : "",
									"text" : "Change rule parameters"
								}

							}
, 							{
								"box" : 								{
									"hidden" : 1,
									"id" : "obj-13",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 763.0, 563.0, 91.0, 23.0 ],
									"style" : "",
									"text" : "loadmess 300"
								}

							}
, 							{
								"box" : 								{
									"hidden" : 1,
									"id" : "obj-5",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 787.0, 511.0, 91.0, 23.0 ],
									"style" : "",
									"text" : "loadmess 100"
								}

							}
, 							{
								"box" : 								{
									"bubble" : 1,
									"id" : "obj-25",
									"linecount" : 2,
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 719.0, 486.5, 146.0, 40.0 ],
									"style" : "",
									"text" : "Change swarm characteristics"
								}

							}
, 							{
								"box" : 								{
									"format" : 6,
									"id" : "obj-24",
									"maxclass" : "flonum",
									"numinlets" : 1,
									"numoutlets" : 2,
									"outlettype" : [ "", "bang" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 559.0, 365.0, 50.0, 23.0 ],
									"style" : ""
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-23",
									"linecount" : 4,
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 559.0, 397.5, 297.0, 67.0 ],
									"style" : "",
									"text" : "changeruleparams 1 leftbarrier (repulsion $1 ), changeruleparams 1 rightbarrier (repulsion $1 ), changeruleparams 1 topbarrier (repulsion $1 ), changeruleparams 1 bottombarrier (repulsion $1 )"
								}

							}
, 							{
								"box" : 								{
									"format" : 6,
									"id" : "obj-18",
									"maxclass" : "flonum",
									"numinlets" : 1,
									"numoutlets" : 2,
									"outlettype" : [ "", "bang" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 559.0, 476.0, 50.0, 23.0 ],
									"style" : ""
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-3",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 559.0, 504.5, 157.0, 23.0 ],
									"style" : "",
									"text" : "swarm 1 ( maxspeed $1 )"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-61",
									"maxclass" : "newobj",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "float" ],
									"patching_rect" : [ 735.0, 310.0, 66.0, 23.0 ],
									"style" : "",
									"text" : "* 0.00125"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-52",
									"linecount" : 2,
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 735.0, 347.0, 136.0, 38.0 ],
									"style" : "",
									"text" : "changeruleparams 1 align (gain $1 )"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-1",
									"maxclass" : "live.dial",
									"numinlets" : 1,
									"numoutlets" : 2,
									"outlettype" : [ "", "float" ],
									"parameter_enable" : 1,
									"patching_rect" : [ 735.0, 252.0, 147.0, 47.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 700.5, 220.8004, 147.0, 47.0 ],
									"saved_attribute_attributes" : 									{
										"valueof" : 										{
											"parameter_longname" : "Steer Towards Barycenter[2]",
											"parameter_shortname" : "Align Bird Directions",
											"parameter_type" : 0,
											"parameter_mmin" : -100.0,
											"parameter_mmax" : 100.0,
											"parameter_unitstyle" : 5
										}

									}
,
									"varname" : "live.dial[2]"
								}

							}
, 							{
								"box" : 								{
									"bubble" : 1,
									"bubbleside" : 2,
									"id" : "obj-42",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 559.0, 205.5, 153.0, 40.0 ],
									"style" : "",
									"text" : "Change rule parameters"
								}

							}
, 							{
								"box" : 								{
									"bubble" : 1,
									"bubbleside" : 2,
									"id" : "obj-41",
									"linecount" : 2,
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 375.0, 30.0, 196.0, 55.0 ],
									"style" : "",
									"text" : "We turn on notification so to catch the play/stop messages"
								}

							}
, 							{
								"box" : 								{
									"attr" : "notify",
									"id" : "obj-40",
									"maxclass" : "attrui",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 348.0, 93.0, 150.0, 23.0 ],
									"style" : "",
									"text_width" : 69.0
								}

							}
, 							{
								"box" : 								{
									"bubble" : 1,
									"id" : "obj-35",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 405.0, 583.5, 107.0, 25.0 ],
									"style" : "",
									"text" : "Turn audio on"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-33",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patcher" : 									{
										"fileversion" : 1,
										"appversion" : 										{
											"major" : 7,
											"minor" : 3,
											"revision" : 4,
											"architecture" : "x64",
											"modernui" : 1
										}
,
										"rect" : [ 0.0, 0.0, 640.0, 480.0 ],
										"bglocked" : 0,
										"openinpresentation" : 0,
										"default_fontsize" : 12.0,
										"default_fontface" : 0,
										"default_fontname" : "Arial",
										"gridonopen" : 1,
										"gridsize" : [ 15.0, 15.0 ],
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
										"boxes" : [ 											{
												"box" : 												{
													"id" : "obj-87",
													"maxclass" : "newobj",
													"numinlets" : 2,
													"numoutlets" : 2,
													"outlettype" : [ "", "" ],
													"patching_rect" : [ 50.0, 135.0, 51.0, 23.0 ],
													"style" : "",
													"text" : "zl nth 1"
												}

											}
, 											{
												"box" : 												{
													"id" : "obj-82",
													"maxclass" : "newobj",
													"numinlets" : 1,
													"numoutlets" : 1,
													"outlettype" : [ "" ],
													"patching_rect" : [ 50.0, 169.0, 144.0, 23.0 ],
													"style" : "",
													"text" : "if $i1 == 100 then bang"
												}

											}
, 											{
												"box" : 												{
													"id" : "obj-29",
													"maxclass" : "newobj",
													"numinlets" : 1,
													"numoutlets" : 1,
													"outlettype" : [ "" ],
													"patching_rect" : [ 50.0, 244.0, 78.0, 23.0 ],
													"style" : "",
													"text" : "prepend set"
												}

											}
, 											{
												"box" : 												{
													"id" : "obj-25",
													"maxclass" : "newobj",
													"numinlets" : 2,
													"numoutlets" : 2,
													"outlettype" : [ "", "" ],
													"patching_rect" : [ 50.0, 217.0, 81.0, 23.0 ],
													"style" : "",
													"text" : "zl group 256"
												}

											}
, 											{
												"box" : 												{
													"id" : "obj-18",
													"maxclass" : "newobj",
													"numinlets" : 3,
													"numoutlets" : 1,
													"outlettype" : [ "" ],
													"patching_rect" : [ 204.5, 169.0, 132.0, 23.0 ],
													"style" : "",
													"text" : "if $f3 > 20 then $f3 1."
												}

											}
, 											{
												"box" : 												{
													"id" : "obj-22",
													"maxclass" : "newobj",
													"numinlets" : 2,
													"numoutlets" : 2,
													"outlettype" : [ "", "" ],
													"patching_rect" : [ 50.0, 100.0, 88.0, 23.0 ],
													"style" : "",
													"text" : "route myflock"
												}

											}
, 											{
												"box" : 												{
													"comment" : "",
													"id" : "obj-31",
													"index" : 1,
													"maxclass" : "inlet",
													"numinlets" : 0,
													"numoutlets" : 1,
													"outlettype" : [ "list" ],
													"patching_rect" : [ 50.0, 40.0, 30.0, 30.0 ],
													"style" : ""
												}

											}
, 											{
												"box" : 												{
													"comment" : "",
													"id" : "obj-32",
													"index" : 1,
													"maxclass" : "outlet",
													"numinlets" : 1,
													"numoutlets" : 0,
													"patching_rect" : [ 50.0, 327.0, 30.0, 30.0 ],
													"style" : ""
												}

											}
 ],
										"lines" : [ 											{
												"patchline" : 												{
													"destination" : [ "obj-25", 0 ],
													"source" : [ "obj-18", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-18", 0 ],
													"order" : 0,
													"source" : [ "obj-22", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-87", 0 ],
													"order" : 1,
													"source" : [ "obj-22", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-29", 0 ],
													"source" : [ "obj-25", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-32", 0 ],
													"source" : [ "obj-29", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-22", 0 ],
													"source" : [ "obj-31", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-25", 0 ],
													"source" : [ "obj-82", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-82", 0 ],
													"source" : [ "obj-87", 0 ]
												}

											}
 ]
									}
,
									"patching_rect" : [ 352.0, 437.0, 86.0, 23.0 ],
									"saved_object_attributes" : 									{
										"description" : "",
										"digest" : "",
										"globalpatchername" : "",
										"style" : "",
										"tags" : ""
									}
,
									"style" : "",
									"text" : "p look_inside"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-66",
									"linecount" : 2,
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 559.0, 308.5, 165.0, 38.0 ],
									"style" : "",
									"text" : "changeruleparams 1 avoid (thresh $1 ) (gain 1.)"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-64",
									"maxclass" : "live.dial",
									"numinlets" : 1,
									"numoutlets" : 2,
									"outlettype" : [ "", "float" ],
									"parameter_enable" : 1,
									"patching_rect" : [ 559.0, 252.0, 147.0, 47.0 ],
									"saved_attribute_attributes" : 									{
										"valueof" : 										{
											"parameter_longname" : "Steer Towards Barycenter[5]",
											"parameter_shortname" : "Avoid Neighbours",
											"parameter_type" : 0,
											"parameter_mmin" : 1.0,
											"parameter_mmax" : 200.0,
											"parameter_initial_enable" : 1,
											"parameter_initial" : [ 1 ],
											"parameter_unitstyle" : 0,
											"parameter_exponent" : 2.0
										}

									}
,
									"varname" : "live.dial[5]"
								}

							}
, 							{
								"box" : 								{
									"hidden" : 1,
									"id" : "obj-68",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 503.5, 536.0, 89.0, 23.0 ],
									"style" : "",
									"text" : "loadmess -35"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-15",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 233.0, 495.0, 43.0, 23.0 ],
									"style" : "",
									"text" : "0 200"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-7",
									"maxclass" : "newobj",
									"numinlets" : 3,
									"numoutlets" : 2,
									"outlettype" : [ "", "" ],
									"patching_rect" : [ 181.0, 529.0, 51.0, 23.0 ],
									"style" : "",
									"text" : "line 20."
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-11",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 181.0, 495.0, 43.0, 23.0 ],
									"style" : "",
									"text" : "1 200"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-14",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 3,
									"outlettype" : [ "", "", "bang" ],
									"patching_rect" : [ 181.0, 458.0, 124.0, 23.0 ],
									"style" : "",
									"text" : "bach.keys play stop"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-16",
									"maxclass" : "newobj",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "signal" ],
									"patching_rect" : [ 352.0, 499.0, 29.5, 23.0 ],
									"style" : "",
									"text" : "*~"
								}

							}
, 							{
								"box" : 								{
									"channels" : 1,
									"id" : "obj-19",
									"maxclass" : "live.gain~",
									"numinlets" : 1,
									"numoutlets" : 4,
									"orientation" : 1,
									"outlettype" : [ "signal", "", "float", "list" ],
									"parameter_enable" : 1,
									"patching_rect" : [ 352.0, 528.0, 110.0, 31.0 ],
									"presentation_rect" : [ 0.0, 0.0, 0.0, 31.0 ],
									"saved_attribute_attributes" : 									{
										"valueof" : 										{
											"parameter_longname" : "live.gain~[1]",
											"parameter_shortname" : "live.gain~",
											"parameter_type" : 0,
											"parameter_mmin" : -70.0,
											"parameter_mmax" : 6.0,
											"parameter_initial_enable" : 1,
											"parameter_initial" : [ -70 ],
											"parameter_unitstyle" : 4
										}

									}
,
									"showname" : 0,
									"varname" : "live.gain~"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-20",
									"local" : 1,
									"maxclass" : "ezdac~",
									"numinlets" : 2,
									"numoutlets" : 0,
									"patching_rect" : [ 352.0, 574.0, 44.0, 44.0 ],
									"prototypename" : "helpfile",
									"style" : ""
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-21",
									"maxclass" : "newobj",
									"numinlets" : 4,
									"numoutlets" : 1,
									"outlettype" : [ "signal" ],
									"patching_rect" : [ 352.0, 465.0, 160.0, 23.0 ],
									"style" : "",
									"text" : "ioscbank~ 100 2205 2205"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-17",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 10.0, 64.0, 727.0, 21.0 ],
									"style" : "",
									"text" : "You can use dada.boids as a controller for synthesis or audio.",
									"textcolor" : [ 0.501961, 0.501961, 0.501961, 1.0 ]
								}

							}
, 							{
								"box" : 								{
									"attr" : "seq",
									"id" : "obj-12",
									"maxclass" : "attrui",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 174.0, 93.0, 150.0, 23.0 ],
									"style" : ""
								}

							}
, 							{
								"box" : 								{
									"bubble" : 1,
									"id" : "obj-10",
									"linecount" : 2,
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 617.0, 71.5, 95.0, 40.0 ],
									"style" : "",
									"text" : "Start/stop sequencing"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-9",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 575.0, 80.0, 35.0, 23.0 ],
									"style" : "",
									"text" : "stop"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-8",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 537.0, 80.0, 34.0, 23.0 ],
									"style" : "",
									"text" : "play"
								}

							}
, 							{
								"box" : 								{
									"attr" : "showspeed",
									"id" : "obj-6",
									"maxclass" : "attrui",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 10.0, 93.0, 150.0, 23.0 ],
									"style" : ""
								}

							}
, 							{
								"box" : 								{
									"hidden" : 1,
									"id" : "obj-34",
									"linecount" : 4,
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ -900.0, 346.0, 713.0, 67.0 ],
									"style" : "",
									"text" : "clear, addswarms ((size 100) (coord uniform 200 100 300 300) (speed uniform 0 0 10 10) (color 0.7 0 0 1) (name myflock) (maxspeed 200) (applyrule center avoid align (wind (gain 0.01) (speed 100 100)) (leftbarrier (position 0) (repulsion 20)) (rightbarrier (position 1600) (repulsion 20)) (topbarrier (position 1460) (repulsion 20)) (bottombarrier (position 0) (repulsion 1000))))"
								}

							}
, 							{
								"box" : 								{
									"bgimage" : "sky.jpg",
									"boids_data_0000000000" : [ "boids", "(", "rules", ")", "(", "swarms", "(", "(", "name", "myflock", ")", "(", "size", 100, ")", "(", "coord", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 979093402, 1083249864, "_x_x_x_x_bach_float64_x_x_x_x_", 2909730734, 1083277220, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 4063714164, 1082158706, "_x_x_x_x_bach_float64_x_x_x_x_", 3356122456, 1083334852, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1849025597, 1083252685, "_x_x_x_x_bach_float64_x_x_x_x_", 623009511, 1083435296, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 4165392204, 1082577222, "_x_x_x_x_bach_float64_x_x_x_x_", 393725628, 1083389144, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3033953215, 1082679828, "_x_x_x_x_bach_float64_x_x_x_x_", 3660988118, 1083090723, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1136120905, 1082840527, "_x_x_x_x_bach_float64_x_x_x_x_", 2594546284, 1083414050, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1794774437, 1082847019, "_x_x_x_x_bach_float64_x_x_x_x_", 1712832817, 1083192121, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2107938358, 1083188734, "_x_x_x_x_bach_float64_x_x_x_x_", 3516942277, 1083207153, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 202034825, 1082178114, "_x_x_x_x_bach_float64_x_x_x_x_", 1350816225, 1083001392, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2358558787, 1083102912, "_x_x_x_x_bach_float64_x_x_x_x_", 1076169500, 1082857575, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2680958483, 1082288410, "_x_x_x_x_bach_float64_x_x_x_x_", 1434286591, 1082694145, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2404077264, 1080645924, "_x_x_x_x_bach_float64_x_x_x_x_", 1697481805, 1083278693, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2655880713, 1082334320, "_x_x_x_x_bach_float64_x_x_x_x_", 963977540, 1083292855, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3890256562, 1082438135, "_x_x_x_x_bach_float64_x_x_x_x_", 907861381, 1083397165, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1638142905, 1083082510, "_x_x_x_x_bach_float64_x_x_x_x_", 498175314, 1083059820, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3988732386, 1083160727, "_x_x_x_x_bach_float64_x_x_x_x_", 3570064635, 1083399061, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2236648988, 1082143979, "_x_x_x_x_bach_float64_x_x_x_x_", 1437140320, 1083155803, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 333763955, 1082332341, "_x_x_x_x_bach_float64_x_x_x_x_", 2526518666, 1082890093, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1084260836, 1082504975, "_x_x_x_x_bach_float64_x_x_x_x_", 2716473236, 1083192457, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1202887622, 1082507371, "_x_x_x_x_bach_float64_x_x_x_x_", 472022822, 1083298447, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3517504670, 1082480541, "_x_x_x_x_bach_float64_x_x_x_x_", 3680592993, 1082635432, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1062589332, 1082721841, "_x_x_x_x_bach_float64_x_x_x_x_", 1878346009, 1082892049, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2110218247, 1083242879, "_x_x_x_x_bach_float64_x_x_x_x_", 2322369908, 1083559501, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3949026630, 1081909035, "_x_x_x_x_bach_float64_x_x_x_x_", 2790125310, 1083503302, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3433127726, 1081790744, "_x_x_x_x_bach_float64_x_x_x_x_", 3447452385, 1083367438, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 698273951, 1083013314, "_x_x_x_x_bach_float64_x_x_x_x_", 2430993886, 1083209269, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2697143639, 1082510310, "_x_x_x_x_bach_float64_x_x_x_x_", 3082957299, 1083555443, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3177303270, 1082658643, "_x_x_x_x_bach_float64_x_x_x_x_", 1920673866, 1082530255, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2916868671, 1083000220, "_x_x_x_x_bach_float64_x_x_x_x_", 651178257, 1083378944, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2179810307, 1083000462, "_x_x_x_x_bach_float64_x_x_x_x_", 1391569241, 1083379517, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3744159642, 1081575029, "_x_x_x_x_bach_float64_x_x_x_x_", 1614502904, 1083294793, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 834695315, 1081862415, "_x_x_x_x_bach_float64_x_x_x_x_", 3835128356, 1083018305, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2509164652, 1082885238, "_x_x_x_x_bach_float64_x_x_x_x_", 2081736304, 1083047428, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2654478822, 1080285622, "_x_x_x_x_bach_float64_x_x_x_x_", 547805770, 1083367108, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 963570286, 1080489949, "_x_x_x_x_bach_float64_x_x_x_x_", 554756716, 1083520022, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1921712132, 1083344478, "_x_x_x_x_bach_float64_x_x_x_x_", 1429996059, 1083277841, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1295030181, 1081182819, "_x_x_x_x_bach_float64_x_x_x_x_", 2066435552, 1083514996, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3993299226, 1081034207, "_x_x_x_x_bach_float64_x_x_x_x_", 910152231, 1083381741, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 97625569, 1082534605, "_x_x_x_x_bach_float64_x_x_x_x_", 2339908006, 1083306141, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2133714148, 1082911391, "_x_x_x_x_bach_float64_x_x_x_x_", 166996004, 1082899611, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3795498307, 1083327706, "_x_x_x_x_bach_float64_x_x_x_x_", 3425211354, 1083482702, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1671091864, 1082335684, "_x_x_x_x_bach_float64_x_x_x_x_", 662551131, 1083098891, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3159406020, 1082526267, "_x_x_x_x_bach_float64_x_x_x_x_", 1896171039, 1083301793, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2294145604, 1082968884, "_x_x_x_x_bach_float64_x_x_x_x_", 2291763952, 1083588058, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 991716542, 1082637930, "_x_x_x_x_bach_float64_x_x_x_x_", 1320852404, 1083414979, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 515755255, 1082703153, "_x_x_x_x_bach_float64_x_x_x_x_", 3614598937, 1083426430, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1094208009, 1082623757, "_x_x_x_x_bach_float64_x_x_x_x_", 3536544636, 1083614998, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 285579297, 1081207822, "_x_x_x_x_bach_float64_x_x_x_x_", 1846714285, 1082962920, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2970956454, 1081795643, "_x_x_x_x_bach_float64_x_x_x_x_", 1490697833, 1083200463, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1634431810, 1083414315, "_x_x_x_x_bach_float64_x_x_x_x_", 2245626089, 1083528134, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3810640433, 1082325791, "_x_x_x_x_bach_float64_x_x_x_x_", 4168463174, 1083563204, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2863231314, 1082722900, "_x_x_x_x_bach_float64_x_x_x_x_", 2958561751, 1083328478, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 622860342, 1083335400, "_x_x_x_x_bach_float64_x_x_x_x_", 3621971442, 1083577288, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2552299678, 1082155942, "_x_x_x_x_bach_float64_x_x_x_x_", 626485015, 1083222609, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3665388892, 1082871923, "_x_x_x_x_bach_float64_x_x_x_x_", 3617436722, 1082691907, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 310156823, 1081431877, "_x_x_x_x_bach_float64_x_x_x_x_", 654121845, 1083213165, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3441712373, 1081400768, "_x_x_x_x_bach_float64_x_x_x_x_", 2974404061, 1083389498, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2349376082, 1082579903, "_x_x_x_x_bach_float64_x_x_x_x_", 4127325178, 1083487509, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3436306649, 1082826899, "_x_x_x_x_bach_float64_x_x_x_x_", 3952750486, 1083612227, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3515796414, 1082902369, "_x_x_x_x_bach_float64_x_x_x_x_", 1131085952, 1083290737, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 308329917, 1081088614, "_x_x_x_x_bach_float64_x_x_x_x_", 2879005952, 1083165137, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 358763827, 1082685292, "_x_x_x_x_bach_float64_x_x_x_x_", 603665332, 1083091757, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1636128095, 1082710970, "_x_x_x_x_bach_float64_x_x_x_x_", 4157443633, 1083557555, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3002658299, 1082328325, "_x_x_x_x_bach_float64_x_x_x_x_", 2039153818, 1083337001, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1308325164, 1083384178, "_x_x_x_x_bach_float64_x_x_x_x_", 3313465094, 1083382388, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1478516674, 1082271862, "_x_x_x_x_bach_float64_x_x_x_x_", 3129704035, 1083435554, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3252938035, 1082130161, "_x_x_x_x_bach_float64_x_x_x_x_", 1870860603, 1083596933, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1989130439, 1081576136, "_x_x_x_x_bach_float64_x_x_x_x_", 1433379857, 1082880791, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1458740471, 1082249040, "_x_x_x_x_bach_float64_x_x_x_x_", 528347118, 1083423690, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 4240511646, 1082505037, "_x_x_x_x_bach_float64_x_x_x_x_", 766319828, 1083192427, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 923836087, 1083289365, "_x_x_x_x_bach_float64_x_x_x_x_", 418210866, 1083188349, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2165287782, 1082680992, "_x_x_x_x_bach_float64_x_x_x_x_", 835679069, 1083234044, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2190176585, 1083206149, "_x_x_x_x_bach_float64_x_x_x_x_", 3786843828, 1083347989, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 4274611070, 1081732649, "_x_x_x_x_bach_float64_x_x_x_x_", 4062203431, 1083416220, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1374682790, 1083181234, "_x_x_x_x_bach_float64_x_x_x_x_", 1098183462, 1083481867, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 74544897, 1082899078, "_x_x_x_x_bach_float64_x_x_x_x_", 3089520583, 1083293129, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3927558553, 1083296433, "_x_x_x_x_bach_float64_x_x_x_x_", 936334779, 1083367296, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1696601551, 1081556734, "_x_x_x_x_bach_float64_x_x_x_x_", 2857682449, 1083523286, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1690003271, 1082022805, "_x_x_x_x_bach_float64_x_x_x_x_", 3621191208, 1082833627, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2357396728, 1082052375, "_x_x_x_x_bach_float64_x_x_x_x_", 2244522903, 1083422919, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1693058150, 1082395373, "_x_x_x_x_bach_float64_x_x_x_x_", 2420356168, 1083489096, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 423611656, 1082325714, "_x_x_x_x_bach_float64_x_x_x_x_", 509180389, 1083228064, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 325848130, 1083095663, "_x_x_x_x_bach_float64_x_x_x_x_", 3149507767, 1083299040, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3116484307, 1082840472, "_x_x_x_x_bach_float64_x_x_x_x_", 2735904365, 1083417480, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2106570346, 1083131098, "_x_x_x_x_bach_float64_x_x_x_x_", 670623304, 1083572057, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1040665878, 1082501107, "_x_x_x_x_bach_float64_x_x_x_x_", 4221102145, 1083009953, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2606643962, 1082823782, "_x_x_x_x_bach_float64_x_x_x_x_", 3521701589, 1083500415, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1420794474, 1081517929, "_x_x_x_x_bach_float64_x_x_x_x_", 3282839795, 1083083460, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2960851754, 1082161688, "_x_x_x_x_bach_float64_x_x_x_x_", 1045876525, 1083291402, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3490339812, 1083226939, "_x_x_x_x_bach_float64_x_x_x_x_", 1310816940, 1083044437, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3959536996, 1082998633, "_x_x_x_x_bach_float64_x_x_x_x_", 922444164, 1083480980, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2271345623, 1082722880, "_x_x_x_x_bach_float64_x_x_x_x_", 666291028, 1083328515, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2270065958, 1082194865, "_x_x_x_x_bach_float64_x_x_x_x_", 1229197376, 1083509782, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1317264656, 1082508211, "_x_x_x_x_bach_float64_x_x_x_x_", 1506377363, 1082830167, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2733115649, 1081231089, "_x_x_x_x_bach_float64_x_x_x_x_", 1808819437, 1083295633, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3335754596, 1082442389, "_x_x_x_x_bach_float64_x_x_x_x_", 2052091362, 1083401471, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3151866885, 1082662486, "_x_x_x_x_bach_float64_x_x_x_x_", 76724283, 1082732537, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 896605223, 1082681025, "_x_x_x_x_bach_float64_x_x_x_x_", 1582834600, 1083234038, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1777606743, 1083455364, "_x_x_x_x_bach_float64_x_x_x_x_", 3986874262, 1083444013, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3513426492, 1081861449, "_x_x_x_x_bach_float64_x_x_x_x_", 3783609479, 1083279767, ")", ")", "(", "speed", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 4011350778, 3225713775, "_x_x_x_x_bach_float64_x_x_x_x_", 1535363052, 1080588355, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2503257538, 3225992066, "_x_x_x_x_bach_float64_x_x_x_x_", 1291926227, 1080572203, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1769374786, 3225043630, "_x_x_x_x_bach_float64_x_x_x_x_", 1432311258, 1080608919, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3955370545, 3219328156, "_x_x_x_x_bach_float64_x_x_x_x_", 3188972908, 1080623096, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1247427511, 3225908878, "_x_x_x_x_bach_float64_x_x_x_x_", 971662745, 1080577367, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2352319094, 3225817401, "_x_x_x_x_bach_float64_x_x_x_x_", 4184255442, 1080582713, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3403452816, 3225812231, "_x_x_x_x_bach_float64_x_x_x_x_", 3606534167, 1080583005, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 479495369, 3225715071, "_x_x_x_x_bach_float64_x_x_x_x_", 2376126533, 1080588287, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 4066728334, 3225602826, "_x_x_x_x_bach_float64_x_x_x_x_", 1111151955, 1080593911, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3311732619, 3225758259, "_x_x_x_x_bach_float64_x_x_x_x_", 1861956045, 1080585987, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2520237609, 3225928813, "_x_x_x_x_bach_float64_x_x_x_x_", 116501610, 1080576156, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1551418376, 3226270974, "_x_x_x_x_bach_float64_x_x_x_x_", 3209520380, 1080552754, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 4220545466, 3226079926, "_x_x_x_x_bach_float64_x_x_x_x_", 710430576, 1080566434, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3691655584, 3225950252, "_x_x_x_x_bach_float64_x_x_x_x_", 4250420170, 1080574834, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2644857310, 3226088288, "_x_x_x_x_bach_float64_x_x_x_x_", 520104744, 1080565868, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1159890074, 3224773215, "_x_x_x_x_bach_float64_x_x_x_x_", 1751247378, 1080613039, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 513977153, 3225812449, "_x_x_x_x_bach_float64_x_x_x_x_", 2544024975, 1080582993, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 258131735, 3225803207, "_x_x_x_x_bach_float64_x_x_x_x_", 3056232586, 1080583512, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3925292583, 3225957271, "_x_x_x_x_bach_float64_x_x_x_x_", 1403703874, 1080574398, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 822730508, 3226555875, "_x_x_x_x_bach_float64_x_x_x_x_", 4140778427, 1080521477, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 4192027907, 3225705922, "_x_x_x_x_bach_float64_x_x_x_x_", 39302778, 1080588765, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 349453376, 3225767016, "_x_x_x_x_bach_float64_x_x_x_x_", 3488489683, 1080585511, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2805680837, 3226483251, "_x_x_x_x_bach_float64_x_x_x_x_", 2994276643, 1080534416, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3724594762, 3225568740, "_x_x_x_x_bach_float64_x_x_x_x_", 1745602510, 1080595518, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3136344555, 3224202802, "_x_x_x_x_bach_float64_x_x_x_x_", 1216985672, 1080618663, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1453183457, 3225832449, "_x_x_x_x_bach_float64_x_x_x_x_", 750918885, 1080581858, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3545505589, 3225600354, "_x_x_x_x_bach_float64_x_x_x_x_", 1675084437, 1080594029, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 709141838, 3225767350, "_x_x_x_x_bach_float64_x_x_x_x_", 2592153997, 1080585493, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3969202999, 3225551308, "_x_x_x_x_bach_float64_x_x_x_x_", 1219268268, 1080596322, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1791064795, 3225362308, "_x_x_x_x_bach_float64_x_x_x_x_", 2180415494, 1080603144, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1470864738, 3226367129, "_x_x_x_x_bach_float64_x_x_x_x_", 2514469836, 1080545271, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2118421717, 3225963127, "_x_x_x_x_bach_float64_x_x_x_x_", 2022641469, 1080574032, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1229114278, 3226353495, "_x_x_x_x_bach_float64_x_x_x_x_", 1450755418, 1080546357, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 787990966, 3226490442, "_x_x_x_x_bach_float64_x_x_x_x_", 1819834826, 1080533178, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3476970089, 3225639496, "_x_x_x_x_bach_float64_x_x_x_x_", 220042160, 1080592130, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 635992943, 3225644154, "_x_x_x_x_bach_float64_x_x_x_x_", 4042618075, 1080591899, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2477778902, 3225461823, "_x_x_x_x_bach_float64_x_x_x_x_", 2429261553, 1080600257, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1794553224, 3226457334, "_x_x_x_x_bach_float64_x_x_x_x_", 2174127263, 1080537880, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3331321360, 3225692857, "_x_x_x_x_bach_float64_x_x_x_x_", 21528789, 1080589441, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3839688269, 3225660555, "_x_x_x_x_bach_float64_x_x_x_x_", 2496268828, 1080591082, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3594386660, 3225001357, "_x_x_x_x_bach_float64_x_x_x_x_", 1981981576, 1080609610, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1208924906, 3225726245, "_x_x_x_x_bach_float64_x_x_x_x_", 3158668288, 1080587699, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1524955396, 3225340280, "_x_x_x_x_bach_float64_x_x_x_x_", 3783430549, 1080603575, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 459556940, 3225438757, "_x_x_x_x_bach_float64_x_x_x_x_", 924212492, 1080601220, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2468184357, 3225739334, "_x_x_x_x_bach_float64_x_x_x_x_", 3024408612, 1080587004, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2231442721, 3223707024, "_x_x_x_x_bach_float64_x_x_x_x_", 1285067371, 1080620654, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1111472615, 3225439100, "_x_x_x_x_bach_float64_x_x_x_x_", 210997076, 1080601206, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1906203228, 3226180273, "_x_x_x_x_bach_float64_x_x_x_x_", 2484780395, 1080559444, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2904847127, 3226550644, "_x_x_x_x_bach_float64_x_x_x_x_", 576170682, 1080522442, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2786522980, 3225046398, "_x_x_x_x_bach_float64_x_x_x_x_", 1995790883, 1080608873, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 4077046606, 3225470634, "_x_x_x_x_bach_float64_x_x_x_x_", 1066470912, 1080599884, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 4155305616, 3225669259, "_x_x_x_x_bach_float64_x_x_x_x_", 1733631036, 1080590644, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1744120581, 3225610565, "_x_x_x_x_bach_float64_x_x_x_x_", 3790399372, 1080593539, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1573529280, 3226464333, "_x_x_x_x_bach_float64_x_x_x_x_", 3750925871, 1080537291, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1808713103, 3225949140, "_x_x_x_x_bach_float64_x_x_x_x_", 29320230, 1080574904, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 4224192479, 3226427649, "_x_x_x_x_bach_float64_x_x_x_x_", 3039287430, 1080540352, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 4274130712, 3225940656, "_x_x_x_x_bach_float64_x_x_x_x_", 2716339251, 1080575428, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3181965422, 3226387295, "_x_x_x_x_bach_float64_x_x_x_x_", 2482040252, 1080543650, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3054076908, 3225469272, "_x_x_x_x_bach_float64_x_x_x_x_", 709202607, 1080599942, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1913408162, 3225522802, "_x_x_x_x_bach_float64_x_x_x_x_", 2706990326, 1080597610, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3832641233, 3226475073, "_x_x_x_x_bach_float64_x_x_x_x_", 2796261470, 1080535813, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3121954778, 3225794853, "_x_x_x_x_bach_float64_x_x_x_x_", 3843113295, 1080583978, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1158677487, 3226177930, "_x_x_x_x_bach_float64_x_x_x_x_", 3013201630, 1080559612, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 251354003, 3226540937, "_x_x_x_x_bach_float64_x_x_x_x_", 940192986, 1080524218, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 451246330, 3225714600, "_x_x_x_x_bach_float64_x_x_x_x_", 940347120, 1080588312, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2955281956, 3225825767, "_x_x_x_x_bach_float64_x_x_x_x_", 1393077353, 1080582239, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3843555054, 3225531220, "_x_x_x_x_bach_float64_x_x_x_x_", 2336381961, 1080597233, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1249282940, 3225655810, "_x_x_x_x_bach_float64_x_x_x_x_", 820142754, 1080591320, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2567270887, 3224977165, "_x_x_x_x_bach_float64_x_x_x_x_", 545226853, 1080609998, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2793811308, 3225958481, "_x_x_x_x_bach_float64_x_x_x_x_", 3693752153, 1080574322, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3287674886, 3226155964, "_x_x_x_x_bach_float64_x_x_x_x_", 1172883505, 1080561177, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2670940340, 3225786577, "_x_x_x_x_bach_float64_x_x_x_x_", 4061338811, 1080584437, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3013265320, 3225814655, "_x_x_x_x_bach_float64_x_x_x_x_", 564527530, 1080582869, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 974785236, 3226283631, "_x_x_x_x_bach_float64_x_x_x_x_", 3679965754, 1080551792, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2030974781, 3224765845, "_x_x_x_x_bach_float64_x_x_x_x_", 3123561215, 1080613141, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 773529848, 3224894740, "_x_x_x_x_bach_float64_x_x_x_x_", 173293020, 1080611276, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 203712775, 3225910292, "_x_x_x_x_bach_float64_x_x_x_x_", 3759992929, 1080577281, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3128326695, 3225438277, "_x_x_x_x_bach_float64_x_x_x_x_", 4282752223, 1080601239, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1161026298, 3225921216, "_x_x_x_x_bach_float64_x_x_x_x_", 2415215980, 1080576619, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2679490600, 3226025225, "_x_x_x_x_bach_float64_x_x_x_x_", 924663507, 1080570064, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 399430188, 3225672884, "_x_x_x_x_bach_float64_x_x_x_x_", 233474538, 1080590461, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 407926735, 3226310892, "_x_x_x_x_bach_float64_x_x_x_x_", 1551949324, 1080549697, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2561563325, 3225490362, "_x_x_x_x_bach_float64_x_x_x_x_", 954842052, 1080599037, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 631680872, 3225490117, "_x_x_x_x_bach_float64_x_x_x_x_", 3677448383, 1080599047, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1498881369, 3225858629, "_x_x_x_x_bach_float64_x_x_x_x_", 130932992, 1080580347, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1531384963, 3225601498, "_x_x_x_x_bach_float64_x_x_x_x_", 3335068088, 1080593974, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3878518597, 3224834418, "_x_x_x_x_bach_float64_x_x_x_x_", 1219175597, 1080612169, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1223528738, 3226178679, "_x_x_x_x_bach_float64_x_x_x_x_", 4231759654, 1080559558, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2947198179, 3226740604, "_x_x_x_x_bach_float64_x_x_x_x_", 1572334256, 1080484106, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1322767787, 3226003229, "_x_x_x_x_bach_float64_x_x_x_x_", 1513677384, 1080571488, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1446882376, 3225118588, "_x_x_x_x_bach_float64_x_x_x_x_", 3430605056, 1080607650, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2364416989, 3225663752, "_x_x_x_x_bach_float64_x_x_x_x_", 54130148, 1080590922, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3220449207, 3225674526, "_x_x_x_x_bach_float64_x_x_x_x_", 3328235333, 1080590377, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 383441167, 3225730676, "_x_x_x_x_bach_float64_x_x_x_x_", 1051186832, 1080587465, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1743082579, 3226324012, "_x_x_x_x_bach_float64_x_x_x_x_", 1025695219, 1080548677, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3834250647, 3225713419, "_x_x_x_x_bach_float64_x_x_x_x_", 4229447956, 1080588373, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2901496748, 3225518780, "_x_x_x_x_bach_float64_x_x_x_x_", 3334671142, 1080597789, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2924534808, 3225786987, "_x_x_x_x_bach_float64_x_x_x_x_", 1146612252, 1080584415, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3892370023, 3225705724, "_x_x_x_x_bach_float64_x_x_x_x_", 1327550885, 1080588775, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2668686643, 3226713157, "_x_x_x_x_bach_float64_x_x_x_x_", 994307626, 1080490076, ")", ")", "(", "intensity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, ")", "(", "intensityspeed", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "maxspeed", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1080623104, ")", "(", "maxintensity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, ")", "(", "color", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1072064102, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, ")", "(", "applyrule", "(", "center", "(", "gain", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1065646817, ")", ")", "(", "avoid", "(", "gain", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, ")", "(", "thresh", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", "(", "maxthresh", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", ")", "(", "align", "(", "gain", "_x_x_x_x_bach_float64_x_x_x_x_", 3145133537, 1068986077, ")", ")", "(", "wind", "(", "gain", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1065646817, ")", "(", "speed", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1081133031, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1082398566, ")", ")", "(", "leftbarrier", "(", "gain", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, ")", "(", "position", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "repulsion", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", "(", "rightbarrier", "(", "gain", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, ")", "(", "position", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1084947166, ")", "(", "repulsion", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", "(", "topbarrier", "(", "gain", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, ")", "(", "position", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1083778839, ")", "(", "repulsion", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", "(", "bottombarrier", "(", "gain", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, ")", "(", "position", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "repulsion", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", ")", ")", ")" ],
									"boids_data_count" : [ 1 ],
									"center" : [ -443.66367, -378.665977 ],
									"fontface" : 0,
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"id" : "obj-4",
									"maxclass" : "dada.boids",
									"notify" : 1,
									"numinlets" : 2,
									"numoutlets" : 4,
									"out" : "nn",
									"outlettype" : [ "", "", "list", "bang" ],
									"patching_rect" : [ 10.0, 125.0, 532.0, 303.0 ],
									"showaxes" : 1,
									"showgridlabels" : 1,
									"shownames" : 0,
									"showspeed" : 0,
									"zoom" : 7.596195
								}

							}
, 							{
								"box" : 								{
									"border" : 0,
									"filename" : "helpname.js",
									"id" : "obj-2",
									"ignoreclick" : 1,
									"jsarguments" : [ "dada.boids" ],
									"maxclass" : "jsui",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 10.0, 10.0, 231.100128, 57.567627 ]
								}

							}
, 							{
								"box" : 								{
									"background" : 1,
									"bgcolor" : [ 1.0, 0.788235, 0.470588, 1.0 ],
									"fontface" : 1,
									"hint" : "",
									"id" : "obj-43",
									"ignoreclick" : 1,
									"legacytextcolor" : 1,
									"maxclass" : "textbutton",
									"numinlets" : 1,
									"numoutlets" : 3,
									"outlettype" : [ "", "", "int" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 719.0, 209.5, 20.0, 20.0 ],
									"rounded" : 60.0,
									"style" : "",
									"text" : "3",
									"textcolor" : [ 0.34902, 0.34902, 0.34902, 1.0 ]
								}

							}
, 							{
								"box" : 								{
									"background" : 1,
									"bgcolor" : [ 1.0, 0.788235, 0.470588, 1.0 ],
									"fontface" : 1,
									"hint" : "",
									"id" : "obj-37",
									"ignoreclick" : 1,
									"legacytextcolor" : 1,
									"maxclass" : "textbutton",
									"numinlets" : 1,
									"numoutlets" : 3,
									"outlettype" : [ "", "", "int" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 522.0, 586.0, 20.0, 20.0 ],
									"rounded" : 60.0,
									"style" : "",
									"text" : "1",
									"textcolor" : [ 0.34902, 0.34902, 0.34902, 1.0 ]
								}

							}
, 							{
								"box" : 								{
									"background" : 1,
									"bgcolor" : [ 1.0, 0.788235, 0.470588, 1.0 ],
									"fontface" : 1,
									"hint" : "",
									"id" : "obj-38",
									"ignoreclick" : 1,
									"legacytextcolor" : 1,
									"maxclass" : "textbutton",
									"numinlets" : 1,
									"numoutlets" : 3,
									"outlettype" : [ "", "", "int" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 717.0, 80.0, 20.0, 20.0 ],
									"rounded" : 60.0,
									"style" : "",
									"text" : "2",
									"textcolor" : [ 0.34902, 0.34902, 0.34902, 1.0 ]
								}

							}
 ],
						"lines" : [ 							{
								"patchline" : 								{
									"destination" : [ "obj-61", 0 ],
									"source" : [ "obj-1", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-7", 0 ],
									"source" : [ "obj-11", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-4", 0 ],
									"source" : [ "obj-12", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-18", 0 ],
									"hidden" : 1,
									"source" : [ "obj-13", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-11", 0 ],
									"source" : [ "obj-14", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-15", 0 ],
									"source" : [ "obj-14", 1 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-7", 0 ],
									"source" : [ "obj-15", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-19", 0 ],
									"source" : [ "obj-16", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-3", 0 ],
									"source" : [ "obj-18", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-20", 1 ],
									"order" : 0,
									"source" : [ "obj-19", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-20", 0 ],
									"order" : 1,
									"source" : [ "obj-19", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-16", 0 ],
									"source" : [ "obj-21", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-4", 0 ],
									"source" : [ "obj-23", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-23", 0 ],
									"source" : [ "obj-24", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-4", 0 ],
									"source" : [ "obj-3", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-21", 0 ],
									"source" : [ "obj-33", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-4", 0 ],
									"hidden" : 1,
									"source" : [ "obj-34", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-14", 0 ],
									"source" : [ "obj-4", 1 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-33", 0 ],
									"source" : [ "obj-4", 2 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-4", 0 ],
									"source" : [ "obj-40", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-24", 0 ],
									"hidden" : 1,
									"order" : 0,
									"source" : [ "obj-5", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-64", 0 ],
									"hidden" : 1,
									"order" : 1,
									"source" : [ "obj-5", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-4", 0 ],
									"source" : [ "obj-52", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-4", 0 ],
									"source" : [ "obj-6", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-52", 0 ],
									"source" : [ "obj-61", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-66", 0 ],
									"source" : [ "obj-64", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-4", 0 ],
									"source" : [ "obj-66", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-19", 0 ],
									"hidden" : 1,
									"source" : [ "obj-68", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-16", 1 ],
									"source" : [ "obj-7", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-4", 0 ],
									"source" : [ "obj-8", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-4", 0 ],
									"source" : [ "obj-9", 0 ]
								}

							}
 ],
						"styles" : [ 							{
								"name" : "jpatcher001",
								"parentstyle" : "",
								"multi" : 0
							}
, 							{
								"name" : "preset001",
								"default" : 								{
									"accentcolor" : [ 0.5, 0.5, 0.5, 1.0 ]
								}
,
								"parentstyle" : "",
								"multi" : 0
							}
 ]
					}
,
					"patching_rect" : [ 28.0, 114.0, 82.0, 22.0 ],
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
					"text" : "p sequencing",
					"varname" : "basic_tab[1]"
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
						"rect" : [ 0.0, 26.0, 976.0, 624.0 ],
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
									"id" : "obj-19",
									"linecount" : 2,
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 550.0, 86.5, 139.0, 40.0 ],
									"style" : "",
									"text" : "Follow more than one swarm"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-18",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 483.0, 95.5, 65.0, 23.0 ],
									"style" : "",
									"text" : "follow 1 3"
								}

							}
, 							{
								"box" : 								{
									"bubble" : 1,
									"id" : "obj-17",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 542.0, 174.0, 118.0, 25.0 ],
									"style" : "",
									"text" : "Don't follow"
								}

							}
, 							{
								"box" : 								{
									"bubble" : 1,
									"id" : "obj-15",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 550.0, 143.0, 130.0, 25.0 ],
									"style" : "",
									"text" : "Follow all swarms"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-14",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 484.0, 174.0, 44.0, 23.0 ],
									"style" : "",
									"text" : "follow"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-13",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 484.0, 143.0, 60.0, 23.0 ],
									"style" : "",
									"text" : "follow all"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-12",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 76.0, 151.0, 35.0, 23.0 ],
									"style" : "",
									"text" : "stop"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-11",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 35.0, 151.0, 34.0, 23.0 ],
									"style" : "",
									"text" : "play"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-9",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 250.0, 120.0, 55.0, 23.0 ],
									"style" : "",
									"text" : "follow 2"
								}

							}
, 							{
								"box" : 								{
									"bubble" : 1,
									"id" : "obj-16",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 307.0, 95.0, 118.0, 25.0 ],
									"style" : "",
									"text" : "Follow a swarm"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-5",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 241.0, 95.0, 55.0, 23.0 ],
									"style" : "",
									"text" : "follow 1"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-1",
									"maxclass" : "preset",
									"numinlets" : 1,
									"numoutlets" : 4,
									"outlettype" : [ "preset", "int", "preset", "int" ],
									"patching_rect" : [ 16.0, 107.0, 53.0, 19.0 ],
									"preset_data" : [ 										{
											"number" : 1,
											"data" : [ 5, "obj-4", "dada.boids", "begin_preset", 7625, 256, "obj-4", "dada.boids", "restore_preset", 0, 250, "setstoredstate", "boids", "(", "rules", ")", "(", "swarms", "(", "(", "name", "swarm1", ")", "(", "size", 200, ")", "(", "coord", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3888527810, 1080859872, "_x_x_x_x_bach_float64_x_x_x_x_", 1132261777, 1081112776, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3218556814, 1081123782, "_x_x_x_x_bach_float64_x_x_x_x_", 2637510003, 1080040121, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 273162240, 1080889344, "_x_x_x_x_bach_float64_x_x_x_x_", 3730428084, 1080027225, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3667183658, 1079338004, "_x_x_x_x_bach_float64_x_x_x_x_", 787518746, 1080380045, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3033331209, 1080064772, "_x_x_x_x_bach_float64_x_x_x_x_", 4166633448, 1079698419, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1939133211, 1081223565, "_x_x_x_x_bach_float64_x_x_x_x_", 3200134394, 1078990460, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1861574459, 1078636445, "_x_x_x_x_bach_float64_x_x_x_x_", 1585324927, 1077350847, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 718476650, 1080003253, "_x_x_x_x_bach_float64_x_x_x_x_", 2283993117, 1079475214, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3622280716, 1080807173, "_x_x_x_x_bach_float64_x_x_x_x_", 2805535043, 1080166561, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2476497363, 1080143081, "_x_x_x_x_bach_float64_x_x_x_x_", 4276525786, 1081134444, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1459713687, 1079229259, "_x_x_x_x_bach_float64_x_x_x_x_", 2424852285, 1080764318, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3390336140, 1079916101, "_x_x_x_x_bach_float64_x_x_x_x_", 48381868, 1079451606, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1008954091, 1074902389, "_x_x_x_x_bach_float64_x_x_x_x_", 2627740607, 1075843551, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 4116887506, 1078287336, "_x_x_x_x_bach_float64_x_x_x_x_", 605173388, 1078926150, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 333289962, 1079823605, "_x_x_x_x_bach_float64_x_x_x_x_", 2587737447, 1075764915, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 884333611, 1079701013, "_x_x_x_x_bach_float64_x_x_x_x_", 3351556664, 1081039131, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1116757425, 1080930008, "_x_x_x_x_bach_float64_x_x_x_x_", 334950388, 1080260602, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3104015978, 1080443700, "_x_x_x_x_bach_float64_x_x_x_x_", 2523755709, 1080867422, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3960156108, 1080236005, "_x_x_x_x_bach_float64_x_x_x_x_", 2766004143, 1079832535, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1900295817, 1080367940, "_x_x_x_x_bach_float64_x_x_x_x_", 894981329, 1080601192, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 975716109, 1080991622, "_x_x_x_x_bach_float64_x_x_x_x_", 337749332, 1081119402, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1507487807, 1080244255, "_x_x_x_x_bach_float64_x_x_x_x_", 335488136, 1080955460, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3552012026, 1080406908, "_x_x_x_x_bach_float64_x_x_x_x_", 3072737662, 1078403262, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 407554282, 1079927925, "_x_x_x_x_bach_float64_x_x_x_x_", 3940959118, 1080795590, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1723476383, 1079252175, "_x_x_x_x_bach_float64_x_x_x_x_", 537518858, 1077473669, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2588290429, 1079973566, "_x_x_x_x_bach_float64_x_x_x_x_", 984234883, 1080958401, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2116612581, 1080686834, "_x_x_x_x_bach_float64_x_x_x_x_", 2988503153, 1080227896, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1212469815, 1081174299, "_x_x_x_x_bach_float64_x_x_x_x_", 2031350061, 1079769238, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 410876828, 1078115790, "_x_x_x_x_bach_float64_x_x_x_x_", 986171755, 1081156789, ")", 256, "obj-4", "dada.boids", "restore_preset", 250, 250, "(", "_x_x_x_x_bach_float64_x_x_x_x_", 309881932, 1081112102, "_x_x_x_x_bach_float64_x_x_x_x_", 1075574299, 1080621837, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3710053356, 1072788981, "_x_x_x_x_bach_float64_x_x_x_x_", 1224570377, 1078246148, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 4262726442, 1080919444, "_x_x_x_x_bach_float64_x_x_x_x_", 2882659027, 1079308649, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3238347326, 1078763806, "_x_x_x_x_bach_float64_x_x_x_x_", 2416964873, 1081014916, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 511748208, 1078744120, "_x_x_x_x_bach_float64_x_x_x_x_", 2427609269, 1078538330, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3614804434, 1079559400, "_x_x_x_x_bach_float64_x_x_x_x_", 3000341145, 1080478028, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3817575650, 1080281712, "_x_x_x_x_bach_float64_x_x_x_x_", 1886239083, 1081220277, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3466616642, 1079127968, "_x_x_x_x_bach_float64_x_x_x_x_", 2194525371, 1079764573, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 712512730, 1078594157, "_x_x_x_x_bach_float64_x_x_x_x_", 3429384832, 1080893759, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3504719626, 1080517508, "_x_x_x_x_bach_float64_x_x_x_x_", 2641250653, 1080272046, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3653845986, 1081090544, "_x_x_x_x_bach_float64_x_x_x_x_", 1494166953, 1080989396, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 4085161542, 1080610594, "_x_x_x_x_bach_float64_x_x_x_x_", 4146330880, 1078066815, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1538721397, 1078690618, "_x_x_x_x_bach_float64_x_x_x_x_", 3544331822, 1080695574, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1072029215, 1079308047, "_x_x_x_x_bach_float64_x_x_x_x_", 414402736, 1078174808, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1754941919, 1080993007, "_x_x_x_x_bach_float64_x_x_x_x_", 3536815858, 1079690104, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 458371416, 1080301740, "_x_x_x_x_bach_float64_x_x_x_x_", 3633498934, 1081173402, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1792643081, 1077987332, "_x_x_x_x_bach_float64_x_x_x_x_", 2025822723, 1079364865, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1796749117, 1079974814, "_x_x_x_x_bach_float64_x_x_x_x_", 189393992, 1077212708, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1217256497, 1079569944, "_x_x_x_x_bach_float64_x_x_x_x_", 2897837123, 1080606241, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2333758283, 1079650725, "_x_x_x_x_bach_float64_x_x_x_x_", 3679754664, 1081117907, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 4080868498, 1077317192, "_x_x_x_x_bach_float64_x_x_x_x_", 639882710, 1080584939, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 4205570090, 1080620052, "_x_x_x_x_bach_float64_x_x_x_x_", 739711658, 1080954197, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3496727234, 1081190752, "_x_x_x_x_bach_float64_x_x_x_x_", 1533450395, 1079987277, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3595987628, 1080669525, "_x_x_x_x_bach_float64_x_x_x_x_", 232043350, 1078221227, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 122280498, 1078652185, "_x_x_x_x_bach_float64_x_x_x_x_", 2956099979, 1081245893, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2276313803, 1080485221, "_x_x_x_x_bach_float64_x_x_x_x_", 2732382557, 1080749230, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2726622489, 1079016076, "_x_x_x_x_bach_float64_x_x_x_x_", 3816531714, 1080873856, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3406914990, 1080242902, "_x_x_x_x_bach_float64_x_x_x_x_", 3811207004, 1080341421, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3922687092, 1079425593, "_x_x_x_x_bach_float64_x_x_x_x_", 3415834922, 1077198996, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1499322929, 1080487192, "_x_x_x_x_bach_float64_x_x_x_x_", 2189347993, 1078814284, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1386893847, 1078143243, "_x_x_x_x_bach_float64_x_x_x_x_", 184341296, 1081076120, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 256, "obj-4", "dada.boids", "restore_preset", 500, 250, 1552742899, 1080818937, "_x_x_x_x_bach_float64_x_x_x_x_", 2511787819, 1081174933, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3708446214, 1076704002, "_x_x_x_x_bach_float64_x_x_x_x_", 4004347920, 1081163783, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2170888987, 1080332685, "_x_x_x_x_bach_float64_x_x_x_x_", 384025172, 1080353066, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1635095109, 1081182498, "_x_x_x_x_bach_float64_x_x_x_x_", 3685466290, 1080254552, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3522143992, 1079038843, "_x_x_x_x_bach_float64_x_x_x_x_", 3864880660, 1080505097, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 4258831846, 1080577778, "_x_x_x_x_bach_float64_x_x_x_x_", 2556847599, 1080701687, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1433523047, 1077471667, "_x_x_x_x_bach_float64_x_x_x_x_", 3565010732, 1080713109, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 776416652, 1078826694, "_x_x_x_x_bach_float64_x_x_x_x_", 562015496, 1079629444, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2322723533, 1077999974, "_x_x_x_x_bach_float64_x_x_x_x_", 1742696131, 1081145185, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 4010131112, 1078517587, "_x_x_x_x_bach_float64_x_x_x_x_", 742719452, 1081098222, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3421746802, 1081006904, "_x_x_x_x_bach_float64_x_x_x_x_", 3667769176, 1079892907, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1780217807, 1081261031, "_x_x_x_x_bach_float64_x_x_x_x_", 2756990877, 1080601550, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 982003227, 1079252749, "_x_x_x_x_bach_float64_x_x_x_x_", 341202908, 1076571118, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1277726141, 1078085342, "_x_x_x_x_bach_float64_x_x_x_x_", 1062087447, 1081087371, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2478524233, 1079944100, "_x_x_x_x_bach_float64_x_x_x_x_", 1646829039, 1076645623, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1791280437, 1081221786, "_x_x_x_x_bach_float64_x_x_x_x_", 2624524207, 1081116631, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2128441725, 1080506558, "_x_x_x_x_bach_float64_x_x_x_x_", 4232430838, 1080550010, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1216737425, 1080948808, "_x_x_x_x_bach_float64_x_x_x_x_", 2342852885, 1077578890, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2164551147, 1079719669, "_x_x_x_x_bach_float64_x_x_x_x_", 2766548969, 1080530932, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 145160664, 1079540972, "_x_x_x_x_bach_float64_x_x_x_x_", 86928428, 1080440342, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 717209436, 1080942510, "_x_x_x_x_bach_float64_x_x_x_x_", 1435033125, 1075080978, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2979399467, 1078789013, "_x_x_x_x_bach_float64_x_x_x_x_", 3189118512, 1081166615, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1881808389, 1079316226, "_x_x_x_x_bach_float64_x_x_x_x_", 1952663695, 1077781575, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1145443275, 1080527333, "_x_x_x_x_bach_float64_x_x_x_x_", 1421694411, 1080732389, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2763441099, 1076584933, "_x_x_x_x_bach_float64_x_x_x_x_", 3673184066, 1075850144, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 784827608, 1081213548, "_x_x_x_x_bach_float64_x_x_x_x_", 1729414963, 1078879129, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3500423952, 1081253255, "_x_x_x_x_bach_float64_x_x_x_x_", 948305047, 1079443019, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 4064607340, 1080589877, "_x_x_x_x_bach_float64_x_x_x_x_", 2400718697, 1080068020, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1956363837, 1080385310, "_x_x_x_x_bach_float64_x_x_x_x_", 2632356083, 1080084601, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 4070254636, 1081218069, "_x_x_x_x_bach_float64_x_x_x_x_", 223034026, 1076731221, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3160377180, 1080345517, "_x_x_x_x_bach_float64_x_x_x_x_", 1197411497, 1079477844, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3634104090, 1080787852, 256, "obj-4", "dada.boids", "restore_preset", 750, 250, "_x_x_x_x_bach_float64_x_x_x_x_", 3610005380, 1079650241, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2652393003, 1079060245, "_x_x_x_x_bach_float64_x_x_x_x_", 651820094, 1080950303, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1652473023, 1079467615, "_x_x_x_x_bach_float64_x_x_x_x_", 3075262524, 1080845341, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 300791258, 1080220397, "_x_x_x_x_bach_float64_x_x_x_x_", 222168168, 1080558132, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3307642182, 1079594658, "_x_x_x_x_bach_float64_x_x_x_x_", 3560866038, 1078542458, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 700596228, 1079844866, "_x_x_x_x_bach_float64_x_x_x_x_", 3355209220, 1080768257, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 456480706, 1079618529, "_x_x_x_x_bach_float64_x_x_x_x_", 2777302977, 1080927200, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 853132880, 1079501608, "_x_x_x_x_bach_float64_x_x_x_x_", 2648355345, 1081252104, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 29430478, 1080363367, "_x_x_x_x_bach_float64_x_x_x_x_", 1433609873, 1079808840, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 4252266978, 1080310000, "_x_x_x_x_bach_float64_x_x_x_x_", 3485554240, 1080011551, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1325577601, 1080679104, "_x_x_x_x_bach_float64_x_x_x_x_", 987369223, 1080559491, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3255857434, 1080539276, "_x_x_x_x_bach_float64_x_x_x_x_", 2330100835, 1079853617, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2393948821, 1080582474, "_x_x_x_x_bach_float64_x_x_x_x_", 4139174844, 1080976861, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 763154288, 1081190328, "_x_x_x_x_bach_float64_x_x_x_x_", 3123557066, 1080482148, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 238340086, 1080714235, "_x_x_x_x_bach_float64_x_x_x_x_", 3583637346, 1081129904, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2046912887, 1078506683, "_x_x_x_x_bach_float64_x_x_x_x_", 2035908679, 1079033891, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 4051327220, 1080667257, "_x_x_x_x_bach_float64_x_x_x_x_", 2540041145, 1080523228, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2791572143, 1080557911, "_x_x_x_x_bach_float64_x_x_x_x_", 4025238234, 1081024876, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3267566, 1079438839, "_x_x_x_x_bach_float64_x_x_x_x_", 3378374236, 1079702317, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 868124158, 1079395071, "_x_x_x_x_bach_float64_x_x_x_x_", 279412894, 1080705103, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1693257117, 1080067790, "_x_x_x_x_bach_float64_x_x_x_x_", 59529284, 1081256994, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3857560668, 1080056365, "_x_x_x_x_bach_float64_x_x_x_x_", 745405266, 1081097641, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3901676360, 1081109923, "_x_x_x_x_bach_float64_x_x_x_x_", 4208871410, 1081107448, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3512176396, 1075562373, "_x_x_x_x_bach_float64_x_x_x_x_", 3000766777, 1077282972, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2742793169, 1079892456, "_x_x_x_x_bach_float64_x_x_x_x_", 2267887685, 1080106018, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2848538033, 1080041176, "_x_x_x_x_bach_float64_x_x_x_x_", 1836622451, 1081250105, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 734300688, 1079002376, "_x_x_x_x_bach_float64_x_x_x_x_", 1561398713, 1081165532, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 355972488, 1080122052, "_x_x_x_x_bach_float64_x_x_x_x_", 3816289488, 1077410407, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3055181124, 1079586465, "_x_x_x_x_bach_float64_x_x_x_x_", 4190235370, 1078392180, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1250519389, 1080112302, "_x_x_x_x_bach_float64_x_x_x_x_", 113801854, 1079917887, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1407314349, 1079964886, "_x_x_x_x_bach_float64_x_x_x_x_", 694717556, 1078085178, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 599214650, 1080403229, "_x_x_x_x_bach_float64_x_x_x_x_", 3946126356, 256, "obj-4", "dada.boids", "restore_preset", 1000, 250, 1081249289, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3160778270, 1077072654, "_x_x_x_x_bach_float64_x_x_x_x_", 1454349085, 1080479118, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2440575965, 1081236974, "_x_x_x_x_bach_float64_x_x_x_x_", 3645138498, 1080505120, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 429220656, 1080963480, "_x_x_x_x_bach_float64_x_x_x_x_", 1027990239, 1080029551, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3073473599, 1079098911, "_x_x_x_x_bach_float64_x_x_x_x_", 490899074, 1074873153, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1070884479, 1080898367, "_x_x_x_x_bach_float64_x_x_x_x_", 1179904957, 1078195678, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3420875246, 1080210678, "_x_x_x_x_bach_float64_x_x_x_x_", 282179108, 1078647570, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1880751161, 1077739036, "_x_x_x_x_bach_float64_x_x_x_x_", 4001332866, 1079230272, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3902078888, 1078755283, "_x_x_x_x_bach_float64_x_x_x_x_", 1192112459, 1079187621, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 4106622392, 1079642843, "_x_x_x_x_bach_float64_x_x_x_x_", 3190749010, 1081179048, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 4122745584, 1079577975, "_x_x_x_x_bach_float64_x_x_x_x_", 555285144, 1078099276, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1002113161, 1080656964, "_x_x_x_x_bach_float64_x_x_x_x_", 3898240694, 1079064410, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1221792969, 1076464228, "_x_x_x_x_bach_float64_x_x_x_x_", 2443155389, 1080052702, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2225275477, 1080983850, "_x_x_x_x_bach_float64_x_x_x_x_", 3924696276, 1080790633, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 525151732, 1079744250, "_x_x_x_x_bach_float64_x_x_x_x_", 2181168925, 1080655758, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2827609337, 1081242236, "_x_x_x_x_bach_float64_x_x_x_x_", 3928971380, 1080437817, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3394772092, 1080299069, "_x_x_x_x_bach_float64_x_x_x_x_", 1588983135, 1080621743, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 4160765388, 1079713509, "_x_x_x_x_bach_float64_x_x_x_x_", 1810664445, 1080378878, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1994032319, 1080115807, "_x_x_x_x_bach_float64_x_x_x_x_", 142747088, 1079775976, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 822148634, 1078492941, "_x_x_x_x_bach_float64_x_x_x_x_", 235576710, 1080774339, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1836443599, 1081177063, "_x_x_x_x_bach_float64_x_x_x_x_", 3190680630, 1078654490, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1998443887, 1081174711, "_x_x_x_x_bach_float64_x_x_x_x_", 3551718728, 1074362019, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 4232036314, 1079500780, "_x_x_x_x_bach_float64_x_x_x_x_", 2056846995, 1078493001, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 4103886984, 1081027651, "_x_x_x_x_bach_float64_x_x_x_x_", 2297464257, 1079329504, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 862888766, 1080218015, "_x_x_x_x_bach_float64_x_x_x_x_", 1228843943, 1079662035, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3636175470, 1080348982, "_x_x_x_x_bach_float64_x_x_x_x_", 2838751107, 1074394049, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 775590266, 1080805565, "_x_x_x_x_bach_float64_x_x_x_x_", 119863372, 1080163366, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 204032318, 1080501407, "_x_x_x_x_bach_float64_x_x_x_x_", 3574536030, 1079937966, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1193023791, 1077283991, "_x_x_x_x_bach_float64_x_x_x_x_", 1634619359, 1079257071, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3365852390, 1081010802, "_x_x_x_x_bach_float64_x_x_x_x_", 2639879443, 1076932233, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 717075246, 1080383895, "_x_x_x_x_bach_float64_x_x_x_x_", 205432558, 1080873847, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3846265226, 1080077508, "_x_x_x_x_bach_float64_x_x_x_x_", 626877774, 1080111783, ")", 256, "obj-4", "dada.boids", "restore_preset", 1250, 250, "(", "_x_x_x_x_bach_float64_x_x_x_x_", 379975436, 1081080710, "_x_x_x_x_bach_float64_x_x_x_x_", 2818113991, 1078231267, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1718739497, 1079636244, "_x_x_x_x_bach_float64_x_x_x_x_", 3199657124, 1079734865, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3970847936, 1080437343, "_x_x_x_x_bach_float64_x_x_x_x_", 1383857839, 1079377751, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 625393128, 1080155892, "_x_x_x_x_bach_float64_x_x_x_x_", 1197333879, 1080225467, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3337430314, 1079480980, "_x_x_x_x_bach_float64_x_x_x_x_", 4254164368, 1080111815, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2769714565, 1077362370, "_x_x_x_x_bach_float64_x_x_x_x_", 434286194, 1079269177, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1898630053, 1079010770, "_x_x_x_x_bach_float64_x_x_x_x_", 3629112068, 1080520065, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2901659697, 1074391064, "_x_x_x_x_bach_float64_x_x_x_x_", 366430912, 1080010080, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 4105586490, 1080599452, "_x_x_x_x_bach_float64_x_x_x_x_", 4118746502, 1081166530, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1391482935, 1078078491, "_x_x_x_x_bach_float64_x_x_x_x_", 556755908, 1078310370, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 739444856, 1080427580, "_x_x_x_x_bach_float64_x_x_x_x_", 2509313251, 1080265329, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 871966482, 1081168777, "_x_x_x_x_bach_float64_x_x_x_x_", 1424511693, 1081059686, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3240621378, 1079704224, "_x_x_x_x_bach_float64_x_x_x_x_", 2469089257, 1080993780, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 9130964, 1080568298, "_x_x_x_x_bach_float64_x_x_x_x_", 3717611978, 1081090276, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2647202043, 1078365309, "_x_x_x_x_bach_float64_x_x_x_x_", 2137113985, 1080255168, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3958216662, 1080052714, "_x_x_x_x_bach_float64_x_x_x_x_", 2646977575, 1081136659, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 961709933, 1080345526, "_x_x_x_x_bach_float64_x_x_x_x_", 2993799605, 1079763162, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1248095219, 1079653881, "_x_x_x_x_bach_float64_x_x_x_x_", 2205516163, 1080639681, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2023494579, 1076234713, "_x_x_x_x_bach_float64_x_x_x_x_", 2849646879, 1079579791, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 834783152, 1079567320, "_x_x_x_x_bach_float64_x_x_x_x_", 1418626731, 1080673109, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1496002117, 1080563490, "_x_x_x_x_bach_float64_x_x_x_x_", 284512268, 1081239558, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1499090055, 1081206339, "_x_x_x_x_bach_float64_x_x_x_x_", 1856781949, 1080467262, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 4145888212, 1081138665, "_x_x_x_x_bach_float64_x_x_x_x_", 2688734909, 1081256798, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 138429870, 1080861399, "_x_x_x_x_bach_float64_x_x_x_x_", 1732070779, 1079486141, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2795955751, 1077900051, "_x_x_x_x_bach_float64_x_x_x_x_", 561316324, 1081147634, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 295592394, 1080602853, "_x_x_x_x_bach_float64_x_x_x_x_", 3566761790, 1078606750, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3000907927, 1079450699, "_x_x_x_x_bach_float64_x_x_x_x_", 114644710, 1081158515, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1081619223, 1080170891, "_x_x_x_x_bach_float64_x_x_x_x_", 2601538393, 1077422508, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 161087678, 1080655967, "_x_x_x_x_bach_float64_x_x_x_x_", 3142417854, 1079951070, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3072231533, 1081115702, "_x_x_x_x_bach_float64_x_x_x_x_", 898549856, 1081156656, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 273883526, 1076990147, "_x_x_x_x_bach_float64_x_x_x_x_", 3250449610, 1077343844, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 256, "obj-4", "dada.boids", "restore_preset", 1500, 250, 1937806395, 1080052253, "_x_x_x_x_bach_float64_x_x_x_x_", 4270040852, 1080808329, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3936101010, 1079841096, "_x_x_x_x_bach_float64_x_x_x_x_", 1481689635, 1081042193, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 537308026, 1080776125, "_x_x_x_x_bach_float64_x_x_x_x_", 1469029389, 1078316550, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2504918205, 1078395486, "_x_x_x_x_bach_float64_x_x_x_x_", 890838840, 1077972892, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2165582897, 1080464920, "_x_x_x_x_bach_float64_x_x_x_x_", 699441858, 1081119073, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3814784006, 1074822658, "_x_x_x_x_bach_float64_x_x_x_x_", 2010187645, 1081246654, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 279369246, 1075014415, "_x_x_x_x_bach_float64_x_x_x_x_", 954518865, 1081222824, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1446364647, 1077338867, "_x_x_x_x_bach_float64_x_x_x_x_", 1915344289, 1078651600, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3809543870, 1081246558, "_x_x_x_x_bach_float64_x_x_x_x_", 3852675638, 1080726810, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 496244954, 1081134189, "_x_x_x_x_bach_float64_x_x_x_x_", 3419881156, 1080860513, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1085486647, 1079221019, "_x_x_x_x_bach_float64_x_x_x_x_", 1523980853, 1080331546, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2656205443, 1080868161, "_x_x_x_x_bach_float64_x_x_x_x_", 954809859, 1080368897, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1670924795, 1078863101, "_x_x_x_x_bach_float64_x_x_x_x_", 1757952971, 1080434149, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 835551364, 1080082498, "_x_x_x_x_bach_float64_x_x_x_x_", 2863690663, 1080408531, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1290919341, 1079176918, "_x_x_x_x_bach_float64_x_x_x_x_", 3448256342, 1080826794, ")", ")", "(", "speed", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1036330931, 1075483609, "_x_x_x_x_bach_float64_x_x_x_x_", 3043126682, 1073821388, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 679786905, 1074945228, "_x_x_x_x_bach_float64_x_x_x_x_", 565493489, 1074945912, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1890699245, 1075897334, "_x_x_x_x_bach_float64_x_x_x_x_", 2814152898, 1075988576, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1287881545, 1075954084, "_x_x_x_x_bach_float64_x_x_x_x_", 1874863791, 1075319639, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3625308522, 1076029620, "_x_x_x_x_bach_float64_x_x_x_x_", 54234472, 1073596084, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 123213072, 1075841672, "_x_x_x_x_bach_float64_x_x_x_x_", 1047955875, 1073431761, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 4128342702, 1074839894, "_x_x_x_x_bach_float64_x_x_x_x_", 3731464616, 1073008851, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3124560600, 1075216747, "_x_x_x_x_bach_float64_x_x_x_x_", 4144700992, 1074106143, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 4209964840, 1074232211, "_x_x_x_x_bach_float64_x_x_x_x_", 2941399104, 1074862111, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1021153375, 1075234863, "_x_x_x_x_bach_float64_x_x_x_x_", 4130417290, 1074828612, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 366986495, 1075831423, "_x_x_x_x_bach_float64_x_x_x_x_", 1475881897, 1073485268, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1710903223, 1073555419, "_x_x_x_x_bach_float64_x_x_x_x_", 86104706, 1075375425, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 4052782960, 1075333047, "_x_x_x_x_bach_float64_x_x_x_x_", 618429781, 1075986090, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2821239824, 1067735559, "_x_x_x_x_bach_float64_x_x_x_x_", 2970109274, 1075847852, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 738319979, 1074851637, "_x_x_x_x_bach_float64_x_x_x_x_", 783357881, 1074826204, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3642266102, 1074546938, "_x_x_x_x_bach_float64_x_x_x_x_", 3692468614, 1074482370, ")", "(", 256, "obj-4", "dada.boids", "restore_preset", 1750, 250, "_x_x_x_x_bach_float64_x_x_x_x_", 1337530879, 1074564351, "_x_x_x_x_bach_float64_x_x_x_x_", 45299500, 1073322902, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1753048419, 1076015793, "_x_x_x_x_bach_float64_x_x_x_x_", 9124486, 1075944771, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2776210828, 1073532613, "_x_x_x_x_bach_float64_x_x_x_x_", 2796308428, 1072047077, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 394909508, 1075899298, "_x_x_x_x_bach_float64_x_x_x_x_", 2839271148, 1072556917, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 854810223, 1074900791, "_x_x_x_x_bach_float64_x_x_x_x_", 129802724, 1075204338, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 4045964212, 1075593689, "_x_x_x_x_bach_float64_x_x_x_x_", 3446623080, 1076078003, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2340355537, 1075281640, "_x_x_x_x_bach_float64_x_x_x_x_", 2090030201, 1074375228, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2871243916, 1075960389, "_x_x_x_x_bach_float64_x_x_x_x_", 1782861723, 1074931661, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2865118712, 1074994939, "_x_x_x_x_bach_float64_x_x_x_x_", 4097369158, 1073508898, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2250593087, 1071819167, "_x_x_x_x_bach_float64_x_x_x_x_", 4265486368, 1073681423, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 682562303, 1075284351, "_x_x_x_x_bach_float64_x_x_x_x_", 4261934736, 1075575623, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 4080114614, 1073270234, "_x_x_x_x_bach_float64_x_x_x_x_", 259616970, 1075099749, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3077543640, 1073204075, "_x_x_x_x_bach_float64_x_x_x_x_", 4291167852, 1074987829, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 567254103, 1075301931, "_x_x_x_x_bach_float64_x_x_x_x_", 3307266930, 1074819512, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 4063507244, 1074928021, "_x_x_x_x_bach_float64_x_x_x_x_", 70130306, 1073155393, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1538495421, 1074907614, "_x_x_x_x_bach_float64_x_x_x_x_", 3578828122, 1074285228, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2642227666, 1074698472, "_x_x_x_x_bach_float64_x_x_x_x_", 212025070, 1072799607, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2977464766, 1073496286, "_x_x_x_x_bach_float64_x_x_x_x_", 2882647830, 1075895178, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1428908211, 1074115673, "_x_x_x_x_bach_float64_x_x_x_x_", 2772019828, 1075893561, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3653955130, 1075148572, "_x_x_x_x_bach_float64_x_x_x_x_", 1735932149, 1073486970, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3770444296, 1075983619, "_x_x_x_x_bach_float64_x_x_x_x_", 3344207036, 1074415197, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 4265007408, 1070296215, "_x_x_x_x_bach_float64_x_x_x_x_", 2965059418, 1072536492, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3543059726, 1072129670, "_x_x_x_x_bach_float64_x_x_x_x_", 1261467211, 1071135525, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1800717147, 1074422189, "_x_x_x_x_bach_float64_x_x_x_x_", 3304243298, 1074880560, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 244982226, 1075908841, "_x_x_x_x_bach_float64_x_x_x_x_", 1380242167, 1074948475, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1223458137, 1074151084, "_x_x_x_x_bach_float64_x_x_x_x_", 2652455376, 1074569447, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1175963197, 1075045150, "_x_x_x_x_bach_float64_x_x_x_x_", 381520061, 1072612446, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1867890597, 1076027346, "_x_x_x_x_bach_float64_x_x_x_x_", 2788705716, 1070342873, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2109947891, 1074896889, "_x_x_x_x_bach_float64_x_x_x_x_", 2644207968, 1075164335, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2353387089, 1073933096, "_x_x_x_x_bach_float64_x_x_x_x_", 2658972434, 1075206536, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2254968925, 1075842094, "_x_x_x_x_bach_float64_x_x_x_x_", 942606825, 1075283188, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 812054099, 256, "obj-4", "dada.boids", "restore_preset", 2000, 250, 1073969961, "_x_x_x_x_bach_float64_x_x_x_x_", 1541066025, 1075668628, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2043882549, 1074894362, "_x_x_x_x_bach_float64_x_x_x_x_", 771133649, 1074481256, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3410931618, 1075795920, "_x_x_x_x_bach_float64_x_x_x_x_", 2599197096, 1075203283, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 296605792, 1076030512, "_x_x_x_x_bach_float64_x_x_x_x_", 1488002915, 1075351473, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1211664059, 1071399773, "_x_x_x_x_bach_float64_x_x_x_x_", 249735244, 1073828902, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2706083484, 1075169101, "_x_x_x_x_bach_float64_x_x_x_x_", 1736405809, 1075820952, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 104371804, 1071401774, "_x_x_x_x_bach_float64_x_x_x_x_", 3660507754, 1070036276, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2084537217, 1069531584, "_x_x_x_x_bach_float64_x_x_x_x_", 1958169121, 1075029264, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1523019131, 1073985213, "_x_x_x_x_bach_float64_x_x_x_x_", 1836206483, 1075389641, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1782335585, 1075717168, "_x_x_x_x_bach_float64_x_x_x_x_", 2612251934, 1075439246, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 962541857, 1075813520, "_x_x_x_x_bach_float64_x_x_x_x_", 893321883, 1074757965, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2935028210, 1075870968, "_x_x_x_x_bach_float64_x_x_x_x_", 1319720267, 1075882661, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2654808894, 1075746206, "_x_x_x_x_bach_float64_x_x_x_x_", 1626398887, 1075867731, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2561904652, 1074382853, "_x_x_x_x_bach_float64_x_x_x_x_", 884330201, 1074456428, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 406701027, 1073668593, "_x_x_x_x_bach_float64_x_x_x_x_", 4164531944, 1070390131, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3058982102, 1075981930, "_x_x_x_x_bach_float64_x_x_x_x_", 3107291042, 1075494864, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3466363070, 1074675806, "_x_x_x_x_bach_float64_x_x_x_x_", 1113854031, 1074923559, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3077214960, 1075136887, "_x_x_x_x_bach_float64_x_x_x_x_", 1806256811, 1074046293, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2612169487, 1074873735, "_x_x_x_x_bach_float64_x_x_x_x_", 909942767, 1072582647, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3324501524, 1071902473, "_x_x_x_x_bach_float64_x_x_x_x_", 104222038, 1076045483, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2921240724, 1075268681, "_x_x_x_x_bach_float64_x_x_x_x_", 3043353882, 1073934988, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2589062106, 1075378668, "_x_x_x_x_bach_float64_x_x_x_x_", 2053126415, 1074797703, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1128400103, 1075380851, "_x_x_x_x_bach_float64_x_x_x_x_", 1184855315, 1074772617, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3344927356, 1075823933, "_x_x_x_x_bach_float64_x_x_x_x_", 1173542755, 1073310641, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2769109864, 1074176435, "_x_x_x_x_bach_float64_x_x_x_x_", 2229410073, 1075383436, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 200203624, 1076063924, "_x_x_x_x_bach_float64_x_x_x_x_", 3778780892, 1071501165, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 4035564398, 1075898806, "_x_x_x_x_bach_float64_x_x_x_x_", 3509560744, 1075827411, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2401542293, 1074942026, "_x_x_x_x_bach_float64_x_x_x_x_", 3604303612, 1076012925, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1906534965, 1072805146, "_x_x_x_x_bach_float64_x_x_x_x_", 1059286123, 1071756853, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 195604706, 1074026609, "_x_x_x_x_bach_float64_x_x_x_x_", 1878313833, 1074423220, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 405481763, 1075680401, "_x_x_x_x_bach_float64_x_x_x_x_", 3704406474, 1075994852, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 454724321, 1074611568, "_x_x_x_x_bach_float64_x_x_x_x_", 256, "obj-4", "dada.boids", "restore_preset", 2250, 250, 3049898756, 1075110273, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3508671884, 1075382981, "_x_x_x_x_bach_float64_x_x_x_x_", 2778993234, 1071778088, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2913707466, 1074123492, "_x_x_x_x_bach_float64_x_x_x_x_", 2013548963, 1075980497, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2385412339, 1074217081, "_x_x_x_x_bach_float64_x_x_x_x_", 1673852467, 1076001561, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610481449, 1074724756, "_x_x_x_x_bach_float64_x_x_x_x_", 477809749, 1074619946, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3254562152, 1074681523, "_x_x_x_x_bach_float64_x_x_x_x_", 1508782981, 1075780034, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 628641085, 1075586718, "_x_x_x_x_bach_float64_x_x_x_x_", 4197278392, 1074180443, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3705015686, 1074988738, "_x_x_x_x_bach_float64_x_x_x_x_", 1762772577, 1074848560, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 234290821, 1075543874, "_x_x_x_x_bach_float64_x_x_x_x_", 3535770438, 1075300770, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 263119034, 1076064349, "_x_x_x_x_bach_float64_x_x_x_x_", 1145550531, 1075043169, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2153724711, 1074765203, "_x_x_x_x_bach_float64_x_x_x_x_", 1629744399, 1070724743, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2816083520, 1075643167, "_x_x_x_x_bach_float64_x_x_x_x_", 3047181588, 1073751689, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2032250675, 1070651289, "_x_x_x_x_bach_float64_x_x_x_x_", 4065240888, 1074221979, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2229412673, 1075384736, "_x_x_x_x_bach_float64_x_x_x_x_", 888210897, 1074299624, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3722074860, 1075129717, "_x_x_x_x_bach_float64_x_x_x_x_", 1427002593, 1074211440, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 133798512, 1075891512, "_x_x_x_x_bach_float64_x_x_x_x_", 1344851101, 1074030158, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1397268337, 1075597240, "_x_x_x_x_bach_float64_x_x_x_x_", 3302726856, 1075695203, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2533947409, 1075870728, "_x_x_x_x_bach_float64_x_x_x_x_", 2611765200, 1075720167, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2833452702, 1075939150, "_x_x_x_x_bach_float64_x_x_x_x_", 2527318813, 1072818574, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 4150151202, 1075258384, "_x_x_x_x_bach_float64_x_x_x_x_", 2644727682, 1073851328, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2808279726, 1074886998, "_x_x_x_x_bach_float64_x_x_x_x_", 1151942715, 1072996381, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2968383684, 1075247201, "_x_x_x_x_bach_float64_x_x_x_x_", 3579423566, 1075107238, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3354779656, 1073410051, "_x_x_x_x_bach_float64_x_x_x_x_", 936494111, 1075372559, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1497715815, 1073916467, "_x_x_x_x_bach_float64_x_x_x_x_", 3601343060, 1074008361, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3994642662, 1075885170, "_x_x_x_x_bach_float64_x_x_x_x_", 3325414108, 1076028781, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3945932736, 1074861023, "_x_x_x_x_bach_float64_x_x_x_x_", 701473685, 1075302858, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 4260937212, 1074552573, "_x_x_x_x_bach_float64_x_x_x_x_", 1790997805, 1074805398, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1084647739, 1076049053, "_x_x_x_x_bach_float64_x_x_x_x_", 3038380028, 1074593789, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1593469309, 1075131582, "_x_x_x_x_bach_float64_x_x_x_x_", 340195638, 1073970331, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 266654888, 1075997268, "_x_x_x_x_bach_float64_x_x_x_x_", 3776292604, 1074451325, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 354514594, 1075886929, "_x_x_x_x_bach_float64_x_x_x_x_", 2414289161, 1075024004, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2401885703, 1075113731, "_x_x_x_x_bach_float64_x_x_x_x_", 95397209, 1075827372, 256, "obj-4", "dada.boids", "restore_preset", 2500, 250, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2636148389, 1073755986, "_x_x_x_x_bach_float64_x_x_x_x_", 1863321701, 1075840050, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 375150797, 1074670694, "_x_x_x_x_bach_float64_x_x_x_x_", 589763121, 1071876376, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3023453872, 1071325015, "_x_x_x_x_bach_float64_x_x_x_x_", 178892222, 1074058975, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 657877417, 1072379092, "_x_x_x_x_bach_float64_x_x_x_x_", 2790599308, 1076008261, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2238741849, 1074282156, "_x_x_x_x_bach_float64_x_x_x_x_", 1310371949, 1075140662, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3124013700, 1074943297, "_x_x_x_x_bach_float64_x_x_x_x_", 3174359678, 1072329022, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2108692927, 1075842271, "_x_x_x_x_bach_float64_x_x_x_x_", 3026864490, 1075913908, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1542672067, 1074898785, "_x_x_x_x_bach_float64_x_x_x_x_", 3266826680, 1075570907, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1494528973, 1075993062, "_x_x_x_x_bach_float64_x_x_x_x_", 3159394186, 1074807748, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2938447082, 1070764660, "_x_x_x_x_bach_float64_x_x_x_x_", 1794745683, 1075630761, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 735371613, 1075474606, "_x_x_x_x_bach_float64_x_x_x_x_", 2769778048, 1075034815, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3549527024, 1075887607, "_x_x_x_x_bach_float64_x_x_x_x_", 2734528048, 1073662743, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1839447655, 1075437363, "_x_x_x_x_bach_float64_x_x_x_x_", 422138567, 1075620195, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1945938185, 1075991684, "_x_x_x_x_bach_float64_x_x_x_x_", 2709196652, 1075677109, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1259906429, 1075860158, "_x_x_x_x_bach_float64_x_x_x_x_", 4234303906, 1073818832, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2632620244, 1074089065, "_x_x_x_x_bach_float64_x_x_x_x_", 1995155901, 1075172574, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1319474455, 1071827595, "_x_x_x_x_bach_float64_x_x_x_x_", 2240671739, 1076033533, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2786667098, 1074566444, "_x_x_x_x_bach_float64_x_x_x_x_", 797627175, 1075931539, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2253977689, 1075084332, "_x_x_x_x_bach_float64_x_x_x_x_", 1982938273, 1074306640, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2822148084, 1070286841, "_x_x_x_x_bach_float64_x_x_x_x_", 694307571, 1073816953, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 4096158488, 1073952139, "_x_x_x_x_bach_float64_x_x_x_x_", 52459338, 1075329957, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1136453381, 1072591746, "_x_x_x_x_bach_float64_x_x_x_x_", 1236842135, 1074551627, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 4259010474, 1074637780, "_x_x_x_x_bach_float64_x_x_x_x_", 632040551, 1075189299, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2502811578, 1074196444, "_x_x_x_x_bach_float64_x_x_x_x_", 4217207494, 1075756386, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2973423180, 1072524069, "_x_x_x_x_bach_float64_x_x_x_x_", 1189443479, 1072872395, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1885456295, 1075897299, "_x_x_x_x_bach_float64_x_x_x_x_", 1190476253, 1074961646, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2376711914, 1075634036, "_x_x_x_x_bach_float64_x_x_x_x_", 2201270785, 1075469568, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3934151984, 1073689239, "_x_x_x_x_bach_float64_x_x_x_x_", 270870344, 1072862116, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 4221237280, 1074625551, "_x_x_x_x_bach_float64_x_x_x_x_", 2065169055, 1074527567, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1665587765, 1073966362, "_x_x_x_x_bach_float64_x_x_x_x_", 2168421808, 1073725143, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2614434612, 1075482009, "_x_x_x_x_bach_float64_x_x_x_x_", 3791019974, 1076047842, ")", "(", 256, "obj-4", "dada.boids", "restore_preset", 2750, 250, "_x_x_x_x_bach_float64_x_x_x_x_", 4127830210, 1075894368, "_x_x_x_x_bach_float64_x_x_x_x_", 4130573170, 1075955128, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2986861656, 1076097579, "_x_x_x_x_bach_float64_x_x_x_x_", 1212173013, 1075324266, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1961937243, 1075340461, "_x_x_x_x_bach_float64_x_x_x_x_", 1815310257, 1074903000, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2766783312, 1075634599, "_x_x_x_x_bach_float64_x_x_x_x_", 3727365360, 1074104951, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1865794459, 1074979277, "_x_x_x_x_bach_float64_x_x_x_x_", 851242113, 1075738176, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 580240141, 1074454918, "_x_x_x_x_bach_float64_x_x_x_x_", 2520275602, 1074539848, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 652277887, 1075346495, "_x_x_x_x_bach_float64_x_x_x_x_", 4016615564, 1072977989, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2218614180, 1072606929, "_x_x_x_x_bach_float64_x_x_x_x_", 454676305, 1075111848, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 997825303, 1075629451, "_x_x_x_x_bach_float64_x_x_x_x_", 1500102583, 1074061275, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2530523595, 1074945253, "_x_x_x_x_bach_float64_x_x_x_x_", 1743899171, 1075373329, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3426143738, 1073440508, "_x_x_x_x_bach_float64_x_x_x_x_", 3364040546, 1074894768, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 239982396, 1076030366, "_x_x_x_x_bach_float64_x_x_x_x_", 819681013, 1075686266, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2418656827, 1075110685, "_x_x_x_x_bach_float64_x_x_x_x_", 1294641039, 1074090951, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2511290780, 1075290317, "_x_x_x_x_bach_float64_x_x_x_x_", 310253854, 1076038799, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 346229262, 1075938567, "_x_x_x_x_bach_float64_x_x_x_x_", 3084013424, 1075390391, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1348279563, 1075220101, "_x_x_x_x_bach_float64_x_x_x_x_", 287155391, 1075761759, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2972368570, 1075142492, "_x_x_x_x_bach_float64_x_x_x_x_", 3040736156, 1073674701, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3200814094, 1075856902, "_x_x_x_x_bach_float64_x_x_x_x_", 3234173790, 1074973102, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2906095504, 1073463239, "_x_x_x_x_bach_float64_x_x_x_x_", 2731733904, 1075935687, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2397603404, 1075594021, "_x_x_x_x_bach_float64_x_x_x_x_", 253933130, 1072782117, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2951592970, 1073143300, "_x_x_x_x_bach_float64_x_x_x_x_", 1101534953, 1071909748, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1347354465, 1075806128, "_x_x_x_x_bach_float64_x_x_x_x_", 1612763365, 1066428530, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2189769005, 1076010134, "_x_x_x_x_bach_float64_x_x_x_x_", 3786599064, 1074361675, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1420019919, 1074914407, "_x_x_x_x_bach_float64_x_x_x_x_", 3865721830, 1075912178, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 571060139, 1074059221, "_x_x_x_x_bach_float64_x_x_x_x_", 1786442967, 1075935851, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2925544504, 1075847707, "_x_x_x_x_bach_float64_x_x_x_x_", 1681726805, 1075220138, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 338316660, 1068836538, "_x_x_x_x_bach_float64_x_x_x_x_", 63604234, 1075921669, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3844471928, 1076035131, "_x_x_x_x_bach_float64_x_x_x_x_", 551689347, 1075908161, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3111868248, 1075686315, "_x_x_x_x_bach_float64_x_x_x_x_", 676435743, 1075891087, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 77088576, 1075848096, "_x_x_x_x_bach_float64_x_x_x_x_", 1390115383, 1075166491, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 967101901, 1071802086, "_x_x_x_x_bach_float64_x_x_x_x_", 1314415925, 1075065498, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2371641627, 256, "obj-4", "dada.boids", "restore_preset", 3000, 250, 1075196045, "_x_x_x_x_bach_float64_x_x_x_x_", 2884319864, 1075158331, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3763040552, 1075689619, "_x_x_x_x_bach_float64_x_x_x_x_", 507320991, 1070501199, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1202966867, 1073342633, "_x_x_x_x_bach_float64_x_x_x_x_", 2610749650, 1075212392, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2966916866, 1074513792, "_x_x_x_x_bach_float64_x_x_x_x_", 1605799633, 1072383848, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2034976089, 1075684012, "_x_x_x_x_bach_float64_x_x_x_x_", 3853423860, 1072122489, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2318222443, 1074176565, "_x_x_x_x_bach_float64_x_x_x_x_", 255234091, 1071335445, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2624793555, 1074894313, "_x_x_x_x_bach_float64_x_x_x_x_", 3559097290, 1070711268, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1827939721, 1074401988, "_x_x_x_x_bach_float64_x_x_x_x_", 2288393677, 1075515110, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2696546344, 1073546259, "_x_x_x_x_bach_float64_x_x_x_x_", 2729290024, 1076024467, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3118631380, 1072776425, "_x_x_x_x_bach_float64_x_x_x_x_", 1043647149, 1070228822, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1876897809, 1075288072, "_x_x_x_x_bach_float64_x_x_x_x_", 2781651922, 1075204584, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1009648501, 1074201018, "_x_x_x_x_bach_float64_x_x_x_x_", 2020764101, 1074869474, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2675835044, 1075773521, "_x_x_x_x_bach_float64_x_x_x_x_", 78507710, 1076033375, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3696490850, 1074396336, "_x_x_x_x_bach_float64_x_x_x_x_", 2257370961, 1075208104, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3241292058, 1075910796, "_x_x_x_x_bach_float64_x_x_x_x_", 2355823487, 1075151295, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3316813112, 1075398299, "_x_x_x_x_bach_float64_x_x_x_x_", 2594861890, 1074084256, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1491696681, 1073004052, "_x_x_x_x_bach_float64_x_x_x_x_", 689621623, 1075930427, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2005432381, 1074019358, "_x_x_x_x_bach_float64_x_x_x_x_", 2184683981, 1072419046, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 4045797806, 1076034774, "_x_x_x_x_bach_float64_x_x_x_x_", 3500940176, 1074138567, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3544543914, 1073920340, "_x_x_x_x_bach_float64_x_x_x_x_", 976580603, 1075492861, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2320147441, 1075139064, "_x_x_x_x_bach_float64_x_x_x_x_", 1419923709, 1073817726, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 909737447, 1075625715, "_x_x_x_x_bach_float64_x_x_x_x_", 4042343860, 1074307801, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3087766106, 1075693868, "_x_x_x_x_bach_float64_x_x_x_x_", 4285160348, 1074081229, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3486658364, 1074861981, "_x_x_x_x_bach_float64_x_x_x_x_", 4028298094, 1075673526, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3165772110, 1075899558, "_x_x_x_x_bach_float64_x_x_x_x_", 2153962169, 1074883932, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3657803746, 1074975728, "_x_x_x_x_bach_float64_x_x_x_x_", 1412742357, 1069178474, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3844444888, 1072875883, "_x_x_x_x_bach_float64_x_x_x_x_", 1098048841, 1074885284, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2024533543, 1073084179, "_x_x_x_x_bach_float64_x_x_x_x_", 2949652312, 1074270123, ")", ")", "(", "intensity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 256, "obj-4", "dada.boids", "restore_preset", 3250, 250, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, 256, "obj-4", "dada.boids", "restore_preset", 3500, 250, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 256, "obj-4", "dada.boids", "restore_preset", 3750, 250, 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, ")", "(", "intensityspeed", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 256, "obj-4", "dada.boids", "restore_preset", 4000, 250, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, 256, "obj-4", "dada.boids", "restore_preset", 4250, 250, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, ")", "(", "maxspeed", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1080623104, ")", "(", "maxintensity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, ")", "(", "color", "_x_x_x_x_bach_float64_x_x_x_x_", 1717986918, 1072064102, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, ")", "(", "applyrule", "(", "center", "(", "gain", "_x_x_x_x_bach_float64_x_x_x_x_", 1202590843, 1065646817, ")", ")", "(", "avoid", "(", "gain", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, ")", "(", "thresh", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1076756480, ")", "(", "maxthresh", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", ")", "(", "align", "(", "gain", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1069547520, ")", ")", "(", "wind", "(", "gain", 256, "obj-4", "dada.boids", "restore_preset", 4500, 250, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1071644672, ")", "(", "speed", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3224633344, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3224633344, ")", ")", "(", "leftbarrier", "(", "gain", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, ")", "(", "position", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "repulsion", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1077149696, ")", ")", "(", "rightbarrier", "(", "gain", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, ")", "(", "position", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1084715008, ")", "(", "repulsion", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1077149696, ")", ")", "(", "topbarrier", "(", "gain", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, ")", "(", "position", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1083932672, ")", "(", "repulsion", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1077149696, ")", ")", "(", "bottombarrier", "(", "gain", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, ")", "(", "position", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "repulsion", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1083129856, ")", ")", ")", ")", "(", "(", "name", "swarm2", ")", "(", "size", 100, ")", "(", "coord", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3846569369, 3226795724, "_x_x_x_x_bach_float64_x_x_x_x_", 2851308608, 1081213471, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1301325410, 3227276081, "_x_x_x_x_bach_float64_x_x_x_x_", 1663263308, 1078702373, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 92233294, 3227823911, "_x_x_x_x_bach_float64_x_x_x_x_", 2545767010, 1080011056, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3190985393, 3227699544, "_x_x_x_x_bach_float64_x_x_x_x_", 2748065245, 3226211054, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1979268177, 3226967592, "_x_x_x_x_bach_float64_x_x_x_x_", 3256425294, 1081134502, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 28344798, 3227402479, "_x_x_x_x_bach_float64_x_x_x_x_", 700699296, 1080715600, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 73626138, 3226777869, "_x_x_x_x_bach_float64_x_x_x_x_", 3871365554, 3225824472, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2882016517, 3227454082, "_x_x_x_x_bach_float64_x_x_x_x_", 2358229282, 1079041168, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 4094637314, 3226770048, "_x_x_x_x_bach_float64_x_x_x_x_", 1828159120, 1078312775, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2725070191, 3227427511, "_x_x_x_x_bach_float64_x_x_x_x_", 1276539887, 1081244151, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3572852060, 3227628205, "_x_x_x_x_bach_float64_x_x_x_x_", 347761727, 1080538655, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2302273211, 3227611997, "_x_x_x_x_bach_float64_x_x_x_x_", 2767996816, 1074668487, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3746644464, 3227656439, "_x_x_x_x_bach_float64_x_x_x_x_", 2181097884, 1079342285, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3200444412, 3227775997, "_x_x_x_x_bach_float64_x_x_x_x_", 1204764745, 1080041508, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1646176525, 3227538566, "_x_x_x_x_bach_float64_x_x_x_x_", 3561876322, 1080784304, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1847192031, 3227645167, "_x_x_x_x_bach_float64_x_x_x_x_", 1658545877, 1080570730, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3873567359, 3226859839, "_x_x_x_x_bach_float64_x_x_x_x_", 35051648, 1075539009, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 531382144, 256, "obj-4", "dada.boids", "restore_preset", 4750, 250, 3227852736, "_x_x_x_x_bach_float64_x_x_x_x_", 2946471896, 3225144300, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 4038414848, 3227855103, "_x_x_x_x_bach_float64_x_x_x_x_", 3214288736, 1080136623, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 960709722, 3227656749, "_x_x_x_x_bach_float64_x_x_x_x_", 4090028366, 3226103974, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 4036230170, 3227811340, "_x_x_x_x_bach_float64_x_x_x_x_", 3818899352, 1079305163, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1579345997, 3227939878, "_x_x_x_x_bach_float64_x_x_x_x_", 2750390840, 1078055195, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2204619339, 3227707685, "_x_x_x_x_bach_float64_x_x_x_x_", 3586230440, 1081410643, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3045499913, 3227701764, "_x_x_x_x_bach_float64_x_x_x_x_", 740609384, 1079994035, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 922075508, 3227312314, "_x_x_x_x_bach_float64_x_x_x_x_", 2132834887, 1080474915, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 884018504, 3227551396, "_x_x_x_x_bach_float64_x_x_x_x_", 2961427462, 1080059394, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1489904311, 3227750747, "_x_x_x_x_bach_float64_x_x_x_x_", 3940277990, 1080192882, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2071764583, 3226881843, "_x_x_x_x_bach_float64_x_x_x_x_", 905058432, 1079905343, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 719011204, 3227786946, "_x_x_x_x_bach_float64_x_x_x_x_", 3233319378, 1081181416, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1822418551, 3226989371, "_x_x_x_x_bach_float64_x_x_x_x_", 682749244, 1079637662, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2444000063, 3227205023, "_x_x_x_x_bach_float64_x_x_x_x_", 3540589928, 1077448370, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 810119224, 3226908700, "_x_x_x_x_bach_float64_x_x_x_x_", 3667491508, 1081343321, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1840862147, 3227232737, "_x_x_x_x_bach_float64_x_x_x_x_", 1574298155, 1081291029, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1032212028, 3227723550, "_x_x_x_x_bach_float64_x_x_x_x_", 236350775, 1080145563, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2271805731, 3227779217, "_x_x_x_x_bach_float64_x_x_x_x_", 162716400, 1079668088, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3501133341, 3227158286, "_x_x_x_x_bach_float64_x_x_x_x_", 3597699430, 1080607922, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3302606563, 3227247473, "_x_x_x_x_bach_float64_x_x_x_x_", 2497640246, 1080949658, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 292687662, 3227551639, "_x_x_x_x_bach_float64_x_x_x_x_", 2734000174, 1080116246, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2904577499, 3227003629, "_x_x_x_x_bach_float64_x_x_x_x_", 3837002304, 3220832549, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3387294397, 3227124062, "_x_x_x_x_bach_float64_x_x_x_x_", 3364104092, 1080857549, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 686746220, 3227907382, "_x_x_x_x_bach_float64_x_x_x_x_", 1161766171, 1081332365, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1706133315, 3227698081, "_x_x_x_x_bach_float64_x_x_x_x_", 2725454701, 3225915830, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 860990892, 3227604694, "_x_x_x_x_bach_float64_x_x_x_x_", 2436750580, 1081421433, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2341151139, 3226767569, "_x_x_x_x_bach_float64_x_x_x_x_", 1231375232, 1080763839, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 430974794, 3227620261, "_x_x_x_x_bach_float64_x_x_x_x_", 275914293, 1080528666, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2465776617, 3227804148, "_x_x_x_x_bach_float64_x_x_x_x_", 3958636684, 1081294917, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 265818490, 3227814077, "_x_x_x_x_bach_float64_x_x_x_x_", 3012749620, 1077769369, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 954154276, 3227229842, "_x_x_x_x_bach_float64_x_x_x_x_", 1873918129, 1080515672, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2174078451, 3227510521, "_x_x_x_x_bach_float64_x_x_x_x_", 256, "obj-4", "dada.boids", "restore_preset", 5000, 250, 3085945516, 1079305557, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 604219480, 3227931692, "_x_x_x_x_bach_float64_x_x_x_x_", 2077787112, 1076904434, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 4192347798, 3227816778, "_x_x_x_x_bach_float64_x_x_x_x_", 593068691, 1081082185, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 913616544, 3226883920, "_x_x_x_x_bach_float64_x_x_x_x_", 1957056064, 3220383526, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3025297051, 3227135821, "_x_x_x_x_bach_float64_x_x_x_x_", 3155349296, 3224725400, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 929958796, 3227256262, "_x_x_x_x_bach_float64_x_x_x_x_", 3431964284, 1080446781, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3317993184, 3227797359, "_x_x_x_x_bach_float64_x_x_x_x_", 2415998920, 1077189602, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1006680340, 3226754186, "_x_x_x_x_bach_float64_x_x_x_x_", 2894663982, 1081395350, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1385997286, 3227603443, "_x_x_x_x_bach_float64_x_x_x_x_", 1489900124, 1080658221, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1601470430, 3227271151, "_x_x_x_x_bach_float64_x_x_x_x_", 646514489, 1081197468, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 149127002, 3227533229, "_x_x_x_x_bach_float64_x_x_x_x_", 138524508, 1077205934, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 4285306902, 3227569162, "_x_x_x_x_bach_float64_x_x_x_x_", 2601936868, 1081373681, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2449523971, 3227837057, "_x_x_x_x_bach_float64_x_x_x_x_", 1038531390, 1080941982, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2184994823, 3227856899, "_x_x_x_x_bach_float64_x_x_x_x_", 3639495974, 1080665746, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 4273817232, 3227722567, "_x_x_x_x_bach_float64_x_x_x_x_", 242328278, 1080643947, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2925632063, 3227569439, "_x_x_x_x_bach_float64_x_x_x_x_", 1654956496, 1078743271, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1529912896, 3227406112, "_x_x_x_x_bach_float64_x_x_x_x_", 2892584426, 1079618292, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2567902887, 3227913043, "_x_x_x_x_bach_float64_x_x_x_x_", 2765064810, 1081083188, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3845913808, 3227778663, "_x_x_x_x_bach_float64_x_x_x_x_", 3937749034, 1081025556, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1849009859, 3227112289, "_x_x_x_x_bach_float64_x_x_x_x_", 4149311958, 1080114410, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1048218870, 3227600507, "_x_x_x_x_bach_float64_x_x_x_x_", 1082583797, 1081259386, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2790565307, 3227275997, "_x_x_x_x_bach_float64_x_x_x_x_", 1286317536, 3220558591, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 43589358, 3227160439, "_x_x_x_x_bach_float64_x_x_x_x_", 3666134738, 1080353640, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1866056591, 3227574727, "_x_x_x_x_bach_float64_x_x_x_x_", 2371112611, 1081108305, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1711884756, 3226969322, "_x_x_x_x_bach_float64_x_x_x_x_", 3168999965, 3225259278, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2534292521, 3227622932, "_x_x_x_x_bach_float64_x_x_x_x_", 2967509212, 1081117805, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1263946376, 3227690308, "_x_x_x_x_bach_float64_x_x_x_x_", 3340946064, 1080157511, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1354226254, 3227544871, "_x_x_x_x_bach_float64_x_x_x_x_", 1293221308, 1079213789, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 414746248, 3227272004, "_x_x_x_x_bach_float64_x_x_x_x_", 1359670460, 3224204895, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 110162782, 3227875759, "_x_x_x_x_bach_float64_x_x_x_x_", 2795073856, 1080899743, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1460241222, 3227566499, "_x_x_x_x_bach_float64_x_x_x_x_", 970566343, 1080513891, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1068059978, 3227625125, "_x_x_x_x_bach_float64_x_x_x_x_", 4158477350, 1081141778, 256, "obj-4", "dada.boids", "restore_preset", 5250, 250, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2384477361, 3227754072, "_x_x_x_x_bach_float64_x_x_x_x_", 2566325412, 1078821457, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3486896443, 3226986653, "_x_x_x_x_bach_float64_x_x_x_x_", 186840194, 1078688321, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3720468344, 3227839419, "_x_x_x_x_bach_float64_x_x_x_x_", 3983582340, 1078612545, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2419582573, 3226792758, "_x_x_x_x_bach_float64_x_x_x_x_", 3493317788, 1078847053, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3759456343, 3227279403, "_x_x_x_x_bach_float64_x_x_x_x_", 3657690996, 1077278648, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1983715185, 3227880376, "_x_x_x_x_bach_float64_x_x_x_x_", 1289710421, 3226318250, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3456104436, 3227614201, "_x_x_x_x_bach_float64_x_x_x_x_", 1075890931, 1081320825, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3608414525, 3226862750, "_x_x_x_x_bach_float64_x_x_x_x_", 3702160474, 1078935084, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2556871469, 3227476374, "_x_x_x_x_bach_float64_x_x_x_x_", 4207962178, 1080603680, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3150552781, 3226849126, "_x_x_x_x_bach_float64_x_x_x_x_", 2395347755, 3225488789, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 235156852, 3226737338, "_x_x_x_x_bach_float64_x_x_x_x_", 3383666212, 1081119505, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 383948384, 3227142960, "_x_x_x_x_bach_float64_x_x_x_x_", 2315352995, 1081212369, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1280440388, 3227647010, "_x_x_x_x_bach_float64_x_x_x_x_", 3439018238, 1081139326, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1045175100, 3227880862, "_x_x_x_x_bach_float64_x_x_x_x_", 1761739135, 3225878719, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3763733921, 3226731216, "_x_x_x_x_bach_float64_x_x_x_x_", 2699592480, 1080476047, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3217154490, 3227709660, "_x_x_x_x_bach_float64_x_x_x_x_", 1907176684, 1080007285, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2003088834, 3227343585, "_x_x_x_x_bach_float64_x_x_x_x_", 2334584629, 1081128858, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1457355188, 3227237594, "_x_x_x_x_bach_float64_x_x_x_x_", 1712607132, 3224774606, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2113648121, 3227835132, "_x_x_x_x_bach_float64_x_x_x_x_", 2038507934, 1078105294, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2653265949, 3227504654, "_x_x_x_x_bach_float64_x_x_x_x_", 2409251134, 1080271006, ")", ")", "(", "speed", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2042682531, 1076391505, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 4160628044, 1077088933, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3999098072, 1076802155, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2986741746, 1074989048, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1482098115, 1077117665, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3894989870, 1074031126, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 82423694, 1075107783, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 857595797, 1075769290, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2283546081, 1076237040, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 4176406882, 1074230448, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3630430542, 1074920614, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 256, "obj-4", "dada.boids", "restore_preset", 5500, 250, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2660733568, 1075562815, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 236049758, 1075374767, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1137145915, 1076608029, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 694923861, 1076222250, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3161764480, 1076517183, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 70601320, 1077060916, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2030608507, 1076121661, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3143785746, 1075916424, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 694832351, 1075127919, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2553558600, 1071258403, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1065345473, 1076359392, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3216090242, 1076941376, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2378117798, 1074764114, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3666689514, 1076797172, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 232170486, 1077105147, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1722831161, 1075325084, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 140150521, 1076708220, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3023473546, 1076053444, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2670546260, 1077061289, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3914129868, 1076785381, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1352874713, 1072799084, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3020248664, 1076013867, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2756670246, 1075296658, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2301425549, 1074166726, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2319383564, 1075805701, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3438332386, 1075340528, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2973748250, 1074783756, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2225943651, 1074174513, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1209208415, 1075939119, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 390124887, 1076390571, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1297176507, 1076407261, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", 256, "obj-4", "dada.boids", "restore_preset", 5750, 250, "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2609751638, 1077072682, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2598021448, 1075664035, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1192605937, 1075502200, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2035493403, 1075418381, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2217727279, 1072163479, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2913299066, 1074967868, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3305102438, 1076358706, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 38720556, 1076324886, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 313439846, 1077107507, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 252435212, 1076227462, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3083638894, 1076251702, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2456067501, 1073893078, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1331609489, 1076322248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1550427511, 1076679355, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3588141050, 1077106684, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2146672961, 1077006496, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 431963433, 1074765460, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2581287154, 1075685496, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1152023955, 1075134153, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 855884647, 1075962291, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2066195693, 1073992310, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1931827641, 1077062876, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3605336526, 1076005094, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 4034544948, 1076699801, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 775306209, 1076043248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 4009336488, 1076940627, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2770542972, 1076990141, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 985259425, 1076686544, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1481946255, 1077041735, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3190071962, 1070747980, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3440796964, 1075524241, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 256, "obj-4", "dada.boids", "restore_preset", 6000, 250, 4204346722, 1076928176, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 291576484, 1076923730, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2404505672, 1075375139, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3660924898, 1076012016, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2959427692, 1076012085, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 841116881, 1070675560, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 937180721, 1076764440, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 4281567032, 1073333147, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 927834471, 1077072051, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3837870544, 1074831591, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 294736333, 1076406502, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1689725253, 1074500770, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3338120626, 1076090584, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3083885084, 1076374797, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 616313693, 1077025198, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3642255152, 1076638615, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 305003004, 1077083390, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1123523257, 1077136732, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 371915489, 1074101616, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3400461514, 1077114468, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2729769632, 1073380687, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 341071219, 1076505273, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 987977071, 1073851063, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3361876558, 1076958502, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 801463925, 1076539194, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3950301948, 1076521341, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 4075797978, 1074257644, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", ")", "(", "intensity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, 256, "obj-4", "dada.boids", "restore_preset", 6250, 250, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 256, "obj-4", "dada.boids", "restore_preset", 6500, 250, 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, ")", "(", "intensityspeed", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 256, "obj-4", "dada.boids", "restore_preset", 6750, 250, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, ")", "(", "maxspeed", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1080623104, ")", "(", "maxintensity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, ")", "(", "color", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 858993459, 1070805811, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, ")", "(", "applyrule", "(", "center", "(", "gain", "_x_x_x_x_bach_float64_x_x_x_x_", 1202590843, 1065646817, ")", ")", "(", "avoid", "(", "gain", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, ")", "(", "thresh", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1076756480, ")", "(", "maxthresh", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", ")", "(", "align", "(", "gain", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1069547520, ")", ")", "(", "rightbarrier", "(", "gain", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, ")", "(", "position", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1080459264, ")", "(", "repulsion", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1077805056, ")", ")", ")", ")", "(", "(", "name", "steadyswarm", ")", "(", "size", 30, ")", "(", "coord", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3446160440, 1082072603, "_x_x_x_x_bach_float64_x_x_x_x_", 3643120212, 1079561513, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3438132024, 1081875867, "_x_x_x_x_bach_float64_x_x_x_x_", 1559362225, 1078132056, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3260034320, 1081742983, "_x_x_x_x_bach_float64_x_x_x_x_", 1996052273, 1079225240, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3136475990, 1082059178, "_x_x_x_x_bach_float64_x_x_x_x_", 2182215143, 1076427507, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 55130254, 1081760839, "_x_x_x_x_bach_float64_x_x_x_x_", 3774849676, 1078317381, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3588296878, 1081968726, "_x_x_x_x_bach_float64_x_x_x_x_", 1483722555, 1078978461, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 579977926, 1081860451, "_x_x_x_x_bach_float64_x_x_x_x_", 1042914197, 1079233994, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3345566812, 1081976365, "_x_x_x_x_bach_float64_x_x_x_x_", 1115807669, 1075900378, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 585379364, 1081792274, "_x_x_x_x_bach_float64_x_x_x_x_", 689239575, 1077836555, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1643283255, 1082032539, "_x_x_x_x_bach_float64_x_x_x_x_", 256, "obj-4", "dada.boids", "restore_preset", 7000, 250, 555752893, 1074794206, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1124991178, 1081966693, "_x_x_x_x_bach_float64_x_x_x_x_", 3311338154, 1077117268, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2651487373, 1081769542, "_x_x_x_x_bach_float64_x_x_x_x_", 330883869, 1078751630, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 434686380, 1081681110, "_x_x_x_x_bach_float64_x_x_x_x_", 138486264, 1079480572, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2064075073, 1081746592, "_x_x_x_x_bach_float64_x_x_x_x_", 1835605865, 1079349172, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3290646334, 1081779102, "_x_x_x_x_bach_float64_x_x_x_x_", 2691195640, 1079325051, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 156128688, 1082010328, "_x_x_x_x_bach_float64_x_x_x_x_", 3614337624, 1078998315, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 612493478, 1081717843, "_x_x_x_x_bach_float64_x_x_x_x_", 3440365626, 1077143580, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2895312732, 1081965485, "_x_x_x_x_bach_float64_x_x_x_x_", 2461415655, 1078991987, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1045722066, 1081752041, "_x_x_x_x_bach_float64_x_x_x_x_", 3556769714, 1078329304, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3380444434, 1082031752, "_x_x_x_x_bach_float64_x_x_x_x_", 913847075, 1079187857, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3277407816, 1081860899, "_x_x_x_x_bach_float64_x_x_x_x_", 2706382276, 1077153505, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1496129509, 1081741298, "_x_x_x_x_bach_float64_x_x_x_x_", 205978571, 1078951397, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 554144290, 1081936145, "_x_x_x_x_bach_float64_x_x_x_x_", 3760987260, 1079119421, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 469794852, 1081851922, "_x_x_x_x_bach_float64_x_x_x_x_", 2473797475, 1079284657, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3678910372, 1081859025, "_x_x_x_x_bach_float64_x_x_x_x_", 378917481, 1077864756, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1818397527, 1081755051, "_x_x_x_x_bach_float64_x_x_x_x_", 3869756102, 1079502178, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1149001738, 1082011653, "_x_x_x_x_bach_float64_x_x_x_x_", 3265909570, 1074063776, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2553731301, 1081814130, "_x_x_x_x_bach_float64_x_x_x_x_", 456513999, 1076554983, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1533244299, 1081948613, "_x_x_x_x_bach_float64_x_x_x_x_", 4055154478, 1077960598, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3526257590, 1081980378, "_x_x_x_x_bach_float64_x_x_x_x_", 2525333735, 1079166067, ")", ")", "(", "speed", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, 256, "obj-4", "dada.boids", "restore_preset", 7250, 250, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", ")", "(", "intensity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, ")", 131, "obj-4", "dada.boids", "restore_preset", 7500, 125, "(", "intensityspeed", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, ")", "(", "maxspeed", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "maxintensity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, ")", "(", "color", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 858993459, 1070805811, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, ")", "(", "applyrule", ")", ")", ")", 4, "obj-4", "dada.boids", "end_preset" ]
										}
 ],
									"style" : ""
								}

							}
, 							{
								"box" : 								{
									"bgimage" : "sky.jpg",
									"boids_data_0000000000" : [ "boids", "(", "rules", ")", "(", "swarms", "(", "(", "name", "swarm1", ")", "(", "size", 200, ")", "(", "coord", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1080859872, "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1081112776, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1081123782, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1080040121, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1080889344, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1080027225, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1079338004, "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1080380045, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1080064772, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079698420, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1081223565, "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1078990460, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1078636445, "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1077350847, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1080003253, "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1079475214, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1080807173, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1080166561, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1080143081, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1081134445, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1079229259, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1080764318, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1079916101, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079451606, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1074902389, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1075843551, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1078287337, "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1078926150, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1079823605, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1075764915, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1079701013, "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1081039131, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1080930008, "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1080260602, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1080443700, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1080867422, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1080236005, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1079832535, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1080367940, "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1080601192, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1080991622, "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1081119402, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1080244255, "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1080955460, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1080406908, "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1078403262, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1079927925, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1080795590, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1079252175, "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1077473669, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1079973566, "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1080958401, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1080686834, "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1080227896, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1081174299, "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1079769238, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1078115790, "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1081156789, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1081112102, "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1080621837, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1072788981, "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1078246148, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1080919445, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1079308649, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1078763806, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1081014916, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1078744120, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1078538330, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1079559400, "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1080478028, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1080281712, "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1081220277, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1079127968, "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1079764573, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1078594157, "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1080893759, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1080517508, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1080272046, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1081090544, "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1080989396, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1080610595, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1078066816, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1078690618, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1080695574, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1079308047, "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1078174808, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1080993007, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1079690104, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1080301740, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1081173402, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1077987332, "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1079364865, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1079974814, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1077212708, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1079569944, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1080606241, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1079650725, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1081117907, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1077317193, "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1080584939, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1080620053, "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1080954197, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1081190752, "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1079987277, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1080669525, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1078221227, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1078652185, "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1081245893, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1080485221, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1080749230, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1079016076, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1080873856, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1080242902, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1080341421, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1079425593, "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1077198996, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1080487192, "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1078814284, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1078143243, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1081076120, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1080818937, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1081174933, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1076704002, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1081163783, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1080332685, "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1080353066, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1081182498, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1080254552, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1079038843, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1080505097, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1080577779, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1080701687, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1077471667, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1080713109, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1078826694, "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1079629444, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1077999974, "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1081145185, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1078517587, "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1081098222, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1081006904, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1079892907, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1081261031, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1080601550, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1079252749, "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1076571118, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1078085342, "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1081087371, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1079944100, "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1076645623, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1081221786, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1081116631, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1080506558, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1080550011, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1080948808, "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1077578890, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1079719669, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1080530932, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079540972, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1080440342, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1080942510, "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1075080978, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1078789013, "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1081166615, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1079316226, "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1077781575, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1080527333, "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1080732389, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1076584933, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1075850144, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1081213548, "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1078879129, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1081253255, "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1079443019, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1080589878, "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1080068020, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1080385310, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1080084601, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1081218070, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1076731221, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1080345517, "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1079477844, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1080787852, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1079650241, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1079060245, "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1080950303, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1079467615, "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1080845341, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1080220397, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1080558132, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1079594658, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1078542458, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1079844866, "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1080768257, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1079618529, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1080927200, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1079501608, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1081252104, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1080363367, "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1079808840, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1080310001, "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1080011551, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1080679104, "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1080559491, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1080539276, "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1079853617, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1080582474, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1080976862, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1081190328, "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1080482148, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1080714235, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1081129904, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1078506683, "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1079033891, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1080667258, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1080523228, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1080557911, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1081024876, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079438839, "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1079702317, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1079395071, "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1080705103, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1080067790, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1081256994, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1080056365, "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1081097641, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1081109923, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1081107449, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1075562373, "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1077282972, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1079892456, "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1080106018, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1080041176, "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1081250105, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1079002376, "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1081165532, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1080122052, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1077410407, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1079586465, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1078392181, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1080112302, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079917887, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1079964886, "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1078085178, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1080403229, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1081249289, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1077072654, "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1080479118, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1081236974, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1080505120, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1080963480, "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1080029551, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1079098911, "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1074873153, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1080898367, "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1078195678, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1080210678, "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1078647570, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1077739036, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1079230272, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1078755283, "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1079187621, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079642844, "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1081179048, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079577976, "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1078099276, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1080656964, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1079064410, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1076464228, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1080052702, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1080983850, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1080790633, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1079744250, "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1080655758, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1081242236, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1080437817, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1080299069, "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1080621743, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079713510, "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1080378878, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1080115807, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079775976, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1078492941, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1080774339, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1081177063, "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1078654490, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1081174711, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1074362019, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079500781, "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1078493001, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1081027652, "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1079329504, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1080218015, "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1079662035, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1080348982, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1074394049, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1080805565, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1080163366, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1080501407, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1079937966, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1077283991, "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1079257071, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1081010802, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1076932233, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1080383895, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1080873847, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1080077508, "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1080111783, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1081080710, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1078231267, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1079636244, "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1079734865, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1080437343, "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1079377751, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1080155892, "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1080225467, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1079480980, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1080111816, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1077362370, "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1079269177, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1079010770, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1080520065, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1074391064, "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1080010080, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1080599453, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1081166531, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1078078491, "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1078310370, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1080427580, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1080265329, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1081168777, "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1081059686, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1079704224, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1080993780, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1080568298, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1081090276, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1078365309, "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1080255168, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1080052714, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1081136659, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1080345526, "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1079763162, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1079653881, "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1080639681, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1076234713, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1079579791, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1079567320, "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1080673109, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1080563490, "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1081239558, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1081206339, "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1080467262, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1081138666, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1081256798, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1080861399, "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1079486141, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1077900051, "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1081147634, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1080602853, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1078606750, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1079450699, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1081158515, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1080170891, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1077422508, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1080655967, "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1079951070, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1081115702, "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1081156656, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1076990147, "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1077343844, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1080052253, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1080808330, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1079841096, "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1081042193, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1080776125, "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1078316550, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1078395486, "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1077972892, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1080464920, "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1081119073, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1074822658, "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1081246654, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1075014415, "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1081222824, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1077338867, "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1078651600, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1081246558, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1080726810, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1081134189, "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1080860513, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1079221019, "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1080331546, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1080868161, "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1080368897, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1078863101, "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1080434149, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1080082498, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1080408531, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1079176918, "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1080826794, ")", ")", "(", "speed", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1075483609, "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1073821388, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1074945228, "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1074945912, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1075897334, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1075988576, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1075954084, "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1075319639, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1076029620, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1073596084, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1075841672, "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1073431761, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1074839895, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1073008851, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1075216747, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1074106144, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1074232212, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1074862111, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1075234863, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1074828613, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1075831423, "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1073485268, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1073555419, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1075375425, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1075333048, "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1075986090, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1067735559, "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1075847852, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1074851637, "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1074826204, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1074546938, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1074482370, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1074564351, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1073322902, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1076015793, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1075944771, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1073532613, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1072047077, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1075899298, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1072556917, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1074900791, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1075204338, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1075593690, "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1076078003, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1075281640, "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1074375228, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1075960389, "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1074931661, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1074994939, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1073508899, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1071819167, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1073681424, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1075284351, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1075575624, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1073270235, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1075099749, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1073204075, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1074987830, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1075301931, "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1074819512, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1074928022, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1073155393, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1074907614, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1074285228, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1074698472, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072799607, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1073496286, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1075895178, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1074115673, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1075893561, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1075148572, "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1073486970, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1075983619, "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1074415197, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1070296216, "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1072536492, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1072129670, "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1071135525, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1074422189, "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1074880560, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1075908841, "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1074948475, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1074151084, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1074569447, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1075045150, "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1072612446, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1076027346, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1070342873, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1074896889, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1075164335, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1073933096, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1075206536, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1075842094, "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1075283188, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1073969961, "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1075668628, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1074894362, "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1074481256, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1075795920, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1075203283, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1076030512, "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1075351473, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1071399773, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1073828902, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1075169101, "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1075820952, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1071401774, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1070036276, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1069531584, "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1075029264, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1073985213, "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1075389641, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1075717168, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1075439246, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1075813520, "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1074757965, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1075870968, "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1075882661, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1075746206, "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1075867731, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1074382853, "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1074456428, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1073668593, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1070390132, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1075981930, "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1075494864, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1074675806, "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1074923559, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1075136887, "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1074046293, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1074873735, "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1072582647, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1071902473, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1076045483, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1075268681, "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1073934988, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1075378668, "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1074797703, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1075380851, "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1074772617, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1075823933, "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1073310641, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1074176435, "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1075383436, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1076063924, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1071501165, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1075898807, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1075827411, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1074942026, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1076012925, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1072805146, "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1071756853, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1074026609, "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1074423220, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1075680401, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1075994852, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1074611568, "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1075110273, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1075382981, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1071778088, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1074123492, "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1075980497, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1074217081, "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1076001561, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1074724756, "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1074619946, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1074681523, "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1075780034, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1075586718, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1074180444, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1074988738, "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1074848560, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1075543874, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1075300770, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1076064349, "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1075043169, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1074765203, "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1070724743, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1075643167, "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1073751689, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1070651289, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1074221980, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1075384736, "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1074299624, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1075129717, "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1074211440, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1075891512, "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1074030158, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1075597240, "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1075695203, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1075870728, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1075720167, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1075939150, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1072818574, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1075258385, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1073851328, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1074886998, "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1072996381, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1075247201, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1075107238, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1073410051, "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1075372559, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1073916467, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1074008361, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1075885170, "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1076028781, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1074861023, "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1075302858, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1074552574, "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1074805398, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1076049053, "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1074593789, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1075131582, "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1073970331, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1075997268, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1074451325, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1075886929, "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1075024004, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1075113731, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1075827372, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1073755986, "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1075840050, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1074670694, "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1071876376, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1071325015, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1074058975, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1072379092, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1076008261, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1074282156, "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1075140662, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1074943297, "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1072329022, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1075842271, "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1075913908, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1074898785, "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1075570907, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1075993062, "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1074807748, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1070764660, "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1075630761, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1075474606, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1075034815, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1075887607, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1073662743, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1075437363, "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1075620195, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1075991684, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1075677109, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1075860158, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1073818833, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1074089065, "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1075172574, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1071827595, "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1076033533, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1074566444, "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1075931539, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1075084332, "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1074306640, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1070286841, "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1073816953, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1073952140, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1075329957, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1072591746, "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1074551627, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1074637781, "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1075189299, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1074196444, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1075756387, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1072524069, "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1072872395, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1075897299, "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1074961646, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1075634036, "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1075469568, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1073689239, "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1072862116, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1074625552, "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1074527567, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1073966362, "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1073725143, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1075482009, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1076047842, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1075894369, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1075955129, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1076097579, "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1075324266, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1075340461, "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1074903000, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1075634599, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1074104951, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1074979277, "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1075738176, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1074454918, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1074539848, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1075346495, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1072977989, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1072606929, "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1075111848, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1075629451, "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1074061275, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1074945253, "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1075373329, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1073440508, "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1074894768, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1076030366, "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1075686266, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1075110685, "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1074090951, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1075290317, "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1076038799, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1075938567, "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1075390391, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1075220101, "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1075761759, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1075142492, "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1073674701, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1075856902, "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1074973102, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1073463239, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1075935687, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1075594021, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072782117, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1073143300, "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1071909748, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1075806128, "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1066428530, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1076010134, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1074361675, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1074914407, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1075912178, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1074059221, "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1075935851, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1075847707, "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1075220138, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1068836538, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1075921669, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1076035131, "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1075908161, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1075686315, "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1075891087, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1075848096, "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1075166491, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1071802086, "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1075065498, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1075196045, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1075158331, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1075689619, "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1070501199, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1073342633, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1075212392, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1074513792, "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1072383848, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1075684012, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1072122489, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1074176565, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1071335445, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1074894313, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1070711268, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1074401988, "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1075515110, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1073546259, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1076024467, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1072776425, "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1070228822, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1075288072, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1075204584, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1074201018, "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1074869474, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1075773521, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1076033375, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1074396336, "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1075208104, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1075910796, "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1075151295, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1075398299, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1074084256, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1073004052, "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1075930427, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1074019358, "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1072419046, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1076034775, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1074138567, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1073920340, "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1075492861, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1075139064, "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1073817726, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1075625715, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1074307802, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1075693868, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1074081230, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1074861981, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1075673527, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1075899558, "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1074883932, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1074975728, "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1069178474, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1072875883, "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1074885284, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1073084179, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1074270123, ")", ")", "(", "intensity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, ")", "(", "intensityspeed", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248 ],
									"boids_data_0000000001" : [ "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, ")", "(", "maxspeed", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1080623104, ")", "(", "maxintensity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, ")", "(", "color", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1072064102, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, ")", "(", "applyrule", "(", "center", "(", "gain", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1065646817, ")", ")", "(", "avoid", "(", "gain", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, ")", "(", "thresh", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1076756480, ")", "(", "maxthresh", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", ")", "(", "align", "(", "gain", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1069547520, ")", ")", "(", "wind", "(", "gain", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1071644672, ")", "(", "speed", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3224633344, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3224633344, ")", ")", "(", "leftbarrier", "(", "gain", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, ")", "(", "position", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "repulsion", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1077149696, ")", ")", "(", "rightbarrier", "(", "gain", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, ")", "(", "position", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1084715008, ")", "(", "repulsion", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1077149696, ")", ")", "(", "topbarrier", "(", "gain", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, ")", "(", "position", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1083932672, ")", "(", "repulsion", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1077149696, ")", ")", "(", "bottombarrier", "(", "gain", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, ")", "(", "position", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "repulsion", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1083129856, ")", ")", ")", ")", "(", "(", "name", "swarm2", ")", "(", "size", 100, ")", "(", "coord", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 3226795724, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1081213471, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 3227276081, "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1078702373, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3227823911, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1080011056, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 3227699544, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 3226211054, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 3226967592, "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1081134502, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3227402479, "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1080715600, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3226777869, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 3225824472, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 3227454082, "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1079041168, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3226770049, "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1078312775, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 3227427511, "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1081244151, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 3227628205, "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1080538655, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 3227611997, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1074668487, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 3227656439, "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1079342285, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 3227775997, "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1080041508, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 3227538566, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1080784304, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 3227645167, "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1080570730, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 3226859839, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1075539009, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 3227852736, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 3225144300, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3227855104, "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1080136623, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 3227656749, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3226103975, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3227811341, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1079305163, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 3227939878, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1078055195, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 3227707685, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1081410643, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 3227701764, "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1079994035, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 3227312314, "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1080474915, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 3227551396, "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1080059394, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 3227750747, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1080192882, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 3226881843, "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1079905343, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 3227786946, "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1081181416, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 3226989371, "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1079637662, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 3227205023, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1077448370, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 3226908700, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1081343321, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 3227232737, "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1081291029, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 3227723550, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1080145563, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 3227779217, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079668088, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 3227158286, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1080607922, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 3227247473, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1080949658, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 3227551639, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1080116246, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 3227003629, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 3220832549, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 3227124062, "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1080857549, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 3227907382, "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1081332365, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 3227698081, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 3225915830, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 3227604694, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1081421433, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 3226767569, "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1080763839, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 3227620261, "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1080528666, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 3227804148, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1081294917, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3227814077, "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1077769369, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 3227229842, "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1080515672, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 3227510521, "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1079305557, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 3227931692, "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1076904434, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3227816779, "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1081082185, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 3226883920, "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 3220383526, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 3227135821, "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 3224725400, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 3227256262, "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1080446781, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 3227797359, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1077189602, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 3226754186, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1081395350, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 3227603443, "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1080658221, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 3227271151, "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1081197468, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3227533229, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1077205934, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3227569163, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1081373681, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 3227837057, "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1080941982, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 3227856899, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1080665746, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3227722568, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1080643947, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 3227569439, "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1078743271, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 3227406112, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1079618292, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 3227913043, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1081083188, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 3227778663, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1081025556, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 3227112289, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1080114411, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 3227600507, "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1081259386, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 3227275997, "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 3220558591, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3227160439, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1080353640, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 3227574727, "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1081108305, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 3226969322, "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 3225259278, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 3227622932, "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1081117805, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 3227690308, "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1080157511, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 3227544871, "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1079213789, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 3227272004, "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 3224204895, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3227875759, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1080899743, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 3227566499, "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1080513891, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 3227625125, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1081141779, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 3227754072, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1078821457, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 3226986653, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1078688321, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 3227839419, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1078612545, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 3226792758, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1078847053, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 3227279403, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1077278648, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 3227880376, "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 3226318250, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 3227614201, "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1081320825, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 3226862750, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1078935084, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 3227476374, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1080603681, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 3226849126, "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 3225488789, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3226737338, "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1081119505, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 3227142960, "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1081212369, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 3227647010, "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1081139326, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 3227880862, "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 3225878719, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 3226731216, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1080476047, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 3227709660, "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1080007285, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 3227343585, "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1081128858, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 3227237594, "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 3224774606, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 3227835132, "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1078105294, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 3227504654, "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1080271006, ")", ")", "(", "speed", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1076391505, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1077088934, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1076802155, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1074989048, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1077117665, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1074031126, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1075107783, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1075769290, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1076237040, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1074230449, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1074920614, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1075562815, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1075374767, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1076608029, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1076222250, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1076517183, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1077060916, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1076121661, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1075916424, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1075127919, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1071258403, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1076359392, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1076941376, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1074764114, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1076797172, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1077105147, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1075325084, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1076708220, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1076053444, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1077061289, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1076785381, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1072799084, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1076013867, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1075296658, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1074166726, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1075805701, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1075340528, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1074783756, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1074174513, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1075939119, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1076390571, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1076407261, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1077072682, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1075664035, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1075502200, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1075418381, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1072163479, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1074967868, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1076358706, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1076324886, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1077107507, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1076227462, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1076251702, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1073893078, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1076322248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1076679355, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1077106684, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1077006496, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1074765460, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1075685496, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1075134153, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1075962291, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1073992310, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1077062876, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1076005094, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1076699802, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1076043248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1076940627, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1076990141, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1076686544, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1077041735, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1070747980, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1075524241, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1076928177, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1076923730, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1075375139, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1076012016, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1076012085, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1070675560, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1076764440, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1073333148, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1077072051, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1074831591, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1076406502, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1074500770, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1076090584, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1076374797, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1077025198, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1076638615, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1077083390, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1077136732, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1074101616, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1077114468, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1073380687, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1076505273, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1073851063, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1076958502, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1076539194, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1076521341, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1074257645, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", ")", "(", "intensity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, ")", "(", "intensityspeed", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, ")", "(", "maxspeed", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1080623104, ")", "(", "maxintensity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, ")", "(", "color", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1070805811, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, ")", "(", "applyrule", "(", "center", "(", "gain", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1065646817, ")", ")", "(", "avoid", "(", "gain", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, ")", "(", "thresh", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1076756480, ")", "(", "maxthresh", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", ")", "(", "align", "(", "gain", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1069547520, ")", ")", "(", "rightbarrier", "(", "gain", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, ")", "(", "position", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1080459264, ")", "(", "repulsion", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1077805056, ")", ")", ")", ")", "(", "(", "name", "steadyswarm", ")", "(", "size", 30, ")", "(", "coord", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1082072603, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1079561513, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1081875867, "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1078132056, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1081742983, "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1079225240, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1082059178, "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1076427507, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1081760839, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1078317381, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1081968726, "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1078978461, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1081860451, "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1079233994, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1081976365, "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1075900378, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1081792274, "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1077836555, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1082032539, "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1074794206, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1081966693, "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1077117268, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1081769542, "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1078751630, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1081681110, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079480572, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1081746592, "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1079349172, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1081779102, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1079325051, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1082010328, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1078998315, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1081717843, "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1077143580, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1081965485, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1078991987, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1081752041, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1078329304, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1082031752, "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1079187857, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1081860899, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1077153505, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1081741298, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1078951397, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1081936145, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1079119421, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1081851922, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1079284657, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1081859025, "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1077864756, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1081755051, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1079502178, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1082011653, "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1074063776, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1081814130, "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1076554983, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1081948613, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1077960599, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1081980378, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1079166067, ")", ")", "(", "speed", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", ")", "(", "intensity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, ")", "(", "intensityspeed", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, ")", "(", "maxspeed", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "maxintensity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, ")", "(", "color", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1070805811, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, ")", "(", "applyrule", ")", ")", ")" ],
									"boids_data_count" : [ 2 ],
									"center" : [ -145.575816, -131.776239 ],
									"fontface" : 0,
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"id" : "obj-4",
									"maxclass" : "dada.boids",
									"numinlets" : 2,
									"numoutlets" : 4,
									"out" : "nn",
									"outlettype" : [ "", "", "list", "bang" ],
									"patching_rect" : [ 16.0, 209.0, 532.0, 303.0 ],
									"showaxes" : 1,
									"showgridlabels" : 1,
									"zoom" : 52.825512
								}

							}
, 							{
								"box" : 								{
									"border" : 0,
									"filename" : "helpname.js",
									"id" : "obj-2",
									"ignoreclick" : 1,
									"jsarguments" : [ "dada.boids" ],
									"maxclass" : "jsui",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 10.0, 10.0, 231.100128, 57.567627 ]
								}

							}
 ],
						"lines" : [ 							{
								"patchline" : 								{
									"destination" : [ "obj-4", 0 ],
									"source" : [ "obj-1", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-4", 0 ],
									"source" : [ "obj-11", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-4", 0 ],
									"source" : [ "obj-12", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-4", 0 ],
									"source" : [ "obj-13", 0 ]
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
									"destination" : [ "obj-4", 0 ],
									"source" : [ "obj-18", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-4", 0 ],
									"source" : [ "obj-5", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-4", 0 ],
									"source" : [ "obj-9", 0 ]
								}

							}
 ],
						"styles" : [ 							{
								"name" : "jpatcher001",
								"parentstyle" : "",
								"multi" : 0
							}
, 							{
								"name" : "preset001",
								"default" : 								{
									"accentcolor" : [ 0.5, 0.5, 0.5, 1.0 ]
								}
,
								"parentstyle" : "",
								"multi" : 0
							}
 ]
					}
,
					"patching_rect" : [ 133.0, 298.0, 60.0, 22.0 ],
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
					"text" : "p follow",
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
						"rect" : [ 0.0, 26.0, 976.0, 624.0 ],
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
									"id" : "obj-13",
									"linecount" : 2,
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 813.0, 247.0, 80.0, 40.0 ],
									"style" : "",
									"text" : "Delete a swarm"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-12",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 711.0, 257.0, 95.0, 23.0 ],
									"style" : "",
									"text" : "deleteswarm 2"
								}

							}
, 							{
								"box" : 								{
									"bubble" : 1,
									"id" : "obj-10",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 94.0, 219.0, 75.0, 25.0 ],
									"style" : "",
									"text" : "Clear all"
								}

							}
, 							{
								"box" : 								{
									"bubble" : 1,
									"bubbleside" : 2,
									"id" : "obj-9",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 371.0, 38.0, 95.0, 40.0 ],
									"style" : "",
									"text" : "Add 2 swarms"
								}

							}
, 							{
								"box" : 								{
									"bubble" : 1,
									"id" : "obj-16",
									"linecount" : 3,
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 418.0, 163.0, 174.0, 54.0 ],
									"style" : "",
									"text" : "This swarm has no rules, and has speed 0, hence won't move!"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-8",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 10.0, 565.0, 190.0, 23.0 ],
									"style" : "",
									"text" : "bach.post Dump @maxdepth 2"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-7",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 713.0, 335.0, 91.0, 23.0 ],
									"style" : "",
									"text" : "dump swarms"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-6",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 713.0, 304.0, 43.0, 23.0 ],
									"style" : "",
									"text" : "dump"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-5",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 53.0, 219.0, 39.0, 23.0 ],
									"style" : "",
									"text" : "clear"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-1",
									"linecount" : 2,
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 33.0, 171.0, 375.0, 38.0 ],
									"style" : "",
									"text" : "addswarms ((size 30) (coord uniform 400 0 100 100) (speed 0 0) (color 0 0 0.3 1) (name steadyswarm))"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-34",
									"linecount" : 5,
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 10.0, 80.0, 738.0, 81.0 ],
									"style" : "",
									"text" : "addswarms ((size 200) (coord uniform 0 0 300 300) (speed uniform 0 0 10 10) (color 0.7 0 0 1) (name swarm1) (maxspeed 200) (applyrule center avoid align (wind (gain 0.5) (speed -20 -20)) (leftbarrier (position 0) (repulsion 20)) (rightbarrier (position 3000) (repulsion 20)) (topbarrier (position 1760) (repulsion 20)) (bottombarrier (position 0) (repulsion 1000)))) ((size 100) (coord uniform -180 -60 100 400) (speed uniform 0 0 20 0) (color 0. 0.3 0 1) (name swarm2) (maxspeed 200) (applyrule center avoid align (rightbarrier (position 180) (repulsion 30))))"
								}

							}
, 							{
								"box" : 								{
									"bgimage" : "sky.jpg",
									"boids_data_0000000000" : [ "boids", "(", "rules", ")", "(", "swarms", ")" ],
									"boids_data_count" : [ 1 ],
									"center" : [ -168.304734, -168.939589 ],
									"fontface" : 0,
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"id" : "obj-4",
									"maxclass" : "dada.boids",
									"numinlets" : 2,
									"numoutlets" : 4,
									"out" : "nn",
									"outlettype" : [ "", "", "list", "bang" ],
									"patching_rect" : [ 10.0, 247.0, 666.0, 294.0 ],
									"showaxes" : 1,
									"showgridlabels" : 1,
									"zoom" : 60.345843
								}

							}
, 							{
								"box" : 								{
									"border" : 0,
									"filename" : "helpname.js",
									"id" : "obj-2",
									"ignoreclick" : 1,
									"jsarguments" : [ "dada.boids" ],
									"maxclass" : "jsui",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 10.0, 10.0, 231.100128, 57.567627 ]
								}

							}
 ],
						"lines" : [ 							{
								"patchline" : 								{
									"destination" : [ "obj-4", 0 ],
									"source" : [ "obj-1", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-4", 0 ],
									"source" : [ "obj-12", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-4", 0 ],
									"source" : [ "obj-34", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-8", 0 ],
									"source" : [ "obj-4", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-4", 0 ],
									"source" : [ "obj-5", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-4", 0 ],
									"source" : [ "obj-6", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-4", 0 ],
									"source" : [ "obj-7", 0 ]
								}

							}
 ],
						"styles" : [ 							{
								"name" : "jpatcher001",
								"parentstyle" : "",
								"multi" : 0
							}
, 							{
								"name" : "preset001",
								"default" : 								{
									"accentcolor" : [ 0.5, 0.5, 0.5, 1.0 ]
								}
,
								"parentstyle" : "",
								"multi" : 0
							}
 ]
					}
,
					"patching_rect" : [ 44.0, 149.0, 102.0, 22.0 ],
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
					"text" : "p \"swarm syntax\"",
					"varname" : "basic_tab[2]"
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
						"rect" : [ 0.0, 26.0, 976.0, 624.0 ],
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
									"id" : "obj-32",
									"maxclass" : "number",
									"maximum" : 200,
									"minimum" : 1,
									"numinlets" : 1,
									"numoutlets" : 2,
									"outlettype" : [ "", "bang" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 525.0, 358.0, 50.0, 23.0 ],
									"style" : ""
								}

							}
, 							{
								"box" : 								{
									"bubble" : 1,
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-30",
									"linecount" : 2,
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 693.5, 301.5, 189.0, 40.0 ],
									"style" : "",
									"text" : "Modify swarm properties (see \"swarm syntax\" tab)"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-9",
									"linecount" : 2,
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 525.0, 301.5, 167.0, 38.0 ],
									"style" : "",
									"text" : "swarm 1 ( color 0. 0. 0. 1. ) (name foo)"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-7",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 525.0, 387.0, 120.0, 23.0 ],
									"style" : "",
									"text" : "swarm 1 ( size $1 )"
								}

							}
, 							{
								"box" : 								{
									"bubble" : 1,
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-29",
									"linecount" : 2,
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 665.0, 171.57251, 188.0, 40.0 ],
									"style" : "",
									"text" : "The same, but with respect to the point (10, 20)"
								}

							}
, 							{
								"box" : 								{
									"fontsize" : 13.0,
									"id" : "obj-28",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 541.5, 178.482819, 118.0, 23.0 ],
									"style" : "",
									"text" : "scale 2 0.8 (10 20)"
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
									"patching_rect" : [ 618.5, 129.57251, 272.0, 40.0 ],
									"style" : "",
									"text" : "Scale shape No.2 by a factor of 0.8 with respect to its barycenter"
								}

							}
, 							{
								"box" : 								{
									"fontsize" : 13.0,
									"id" : "obj-26",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 541.5, 137.702271, 73.0, 23.0 ],
									"style" : "",
									"text" : "scale 2 0.8"
								}

							}
, 							{
								"box" : 								{
									"bubble" : 1,
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-22",
									"linecount" : 3,
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 687.5, 76.454193, 180.0, 54.0 ],
									"style" : "",
									"text" : "The same, but with respect ot the individuals shape barycenters"
								}

							}
, 							{
								"box" : 								{
									"fontsize" : 13.0,
									"id" : "obj-23",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 541.5, 89.055328, 144.0, 23.0 ],
									"style" : "",
									"text" : "scale all 1.1 barycenter"
								}

							}
, 							{
								"box" : 								{
									"bubble" : 1,
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-24",
									"linecount" : 2,
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 628.5, 43.0, 220.0, 40.0 ],
									"style" : "",
									"text" : "Scale all shapes by a factor of 1.1, with respect to the origin"
								}

							}
, 							{
								"box" : 								{
									"fontsize" : 13.0,
									"id" : "obj-25",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 541.5, 54.910309, 79.0, 23.0 ],
									"style" : "",
									"text" : "scale all 1.1"
								}

							}
, 							{
								"box" : 								{
									"bubble" : 1,
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-20",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 656.5, 240.675568, 272.0, 25.0 ],
									"style" : "",
									"text" : "Move shape No. 1 by a vector of (-20, -10)"
								}

							}
, 							{
								"box" : 								{
									"fontsize" : 13.0,
									"id" : "obj-21",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 541.5, 240.675568, 107.0, 23.0 ],
									"style" : "",
									"text" : "move 2 (-20 -10)"
								}

							}
, 							{
								"box" : 								{
									"bubble" : 1,
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-19",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 651.5, 215.473297, 252.0, 25.0 ],
									"style" : "",
									"text" : "Move all shapes by a vector of (20, 30)"
								}

							}
, 							{
								"box" : 								{
									"fontsize" : 13.0,
									"id" : "obj-18",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 541.5, 215.473297, 104.0, 23.0 ],
									"style" : "",
									"text" : "move all (20 30)"
								}

							}
, 							{
								"box" : 								{
									"bubble" : 1,
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-16",
									"linecount" : 3,
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 305.0, 225.175568, 214.5, 54.0 ],
									"style" : "",
									"text" : "Indiviually rotate all shapes by 30 degrees around their respective baricenters"
								}

							}
, 							{
								"box" : 								{
									"fontsize" : 13.0,
									"id" : "obj-17",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 109.5, 237.347397, 185.0, 23.0 ],
									"style" : "",
									"text" : "rotate all ( 30 deg ) barycenter"
								}

							}
, 							{
								"box" : 								{
									"bubble" : 1,
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-14",
									"linecount" : 2,
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 262.0, 192.210922, 267.5, 40.0 ],
									"style" : "",
									"text" : "Rotate all shapes by 30 degrees around the point (0, 20)"
								}

							}
, 							{
								"box" : 								{
									"fontsize" : 13.0,
									"id" : "obj-15",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 97.5, 200.710922, 157.0, 23.0 ],
									"style" : "",
									"text" : "rotate all ( 30 deg ) (0 20)"
								}

							}
, 							{
								"box" : 								{
									"bubble" : 1,
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-12",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 208.0, 127.138954, 315.0, 25.0 ],
									"style" : "",
									"text" : "Rotate all shapes by 30 degrees around the origin"
								}

							}
, 							{
								"box" : 								{
									"fontsize" : 13.0,
									"id" : "obj-13",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 77.0, 127.138954, 120.0, 23.0 ],
									"style" : "",
									"text" : "rotate all ( 30 deg )"
								}

							}
, 							{
								"box" : 								{
									"bubble" : 1,
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-10",
									"linecount" : 2,
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 262.0, 155.508682, 275.5, 40.0 ],
									"style" : "",
									"text" : "Rotate shape No. 3 of 5 degrees around the point (50, 60)"
								}

							}
, 							{
								"box" : 								{
									"fontsize" : 13.0,
									"id" : "obj-11",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 88.0, 155.508682, 151.0, 23.0 ],
									"style" : "",
									"text" : "rotate 3 ( 5 deg ) (50 60)"
								}

							}
, 							{
								"box" : 								{
									"bubble" : 1,
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-8",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 149.0, 97.235733, 351.0, 25.0 ],
									"style" : "",
									"text" : "Rotate shape No. 3 by 30 degrees around its barycenter"
								}

							}
, 							{
								"box" : 								{
									"fontsize" : 13.0,
									"id" : "obj-3",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 33.0, 98.769234, 114.0, 23.0 ],
									"style" : "",
									"text" : "rotate 3 ( 30 deg )"
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
									"patching_rect" : [ 93.0, 75.0, 351.0, 25.0 ],
									"style" : "",
									"text" : "Rotate shape No. 1 by 0.5 radians around its barycenter"
								}

							}
, 							{
								"box" : 								{
									"fontsize" : 13.0,
									"id" : "obj-4",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 10.0, 75.766747, 76.0, 23.0 ],
									"style" : "",
									"text" : "rotate 1 0.5"
								}

							}
, 							{
								"box" : 								{
									"bgimage" : "sky.jpg",
									"boids_data_0000000000" : [ "boids", "(", "rules", ")", "(", "swarms", "(", "(", "name", "swarm1", ")", "(", "size", 200, ")", "(", "coord", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1081216052, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1080088881, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1079066701, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1081109569, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1075901973, "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1078000116, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1078343192, "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1080711370, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1079420711, "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1079782695, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1078263910, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1078419735, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1080383927, "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1081248494, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1078667811, "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1080713839, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1078704992, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1079274463, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1079387641, "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1079388784, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1078872730, "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1076864695, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1080469181, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1075340844, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1080778368, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1080177606, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1073474958, "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1080922627, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1076421357, "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1077975846, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1080589887, "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1080226259, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1080781925, "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1080981590, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1079306583, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1078120479, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1081177222, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1079655074, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1080837068, "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1081164105, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1081197146, "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1081104051, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1080336568, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1077959044, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1081173063, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1080137566, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1078666063, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1080740238, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1080757399, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1077535479, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1079181509, "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1080084518, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1079890423, "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1080220195, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1079224016, "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1080940984, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1080415808, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1075110398, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1080166210, "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1077165910, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1079546238, "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1080458248, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1079181674, "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1074484744, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1080046786, "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1079680907, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1077544085, "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1080483676, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1078399216, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1080183794, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1079537878, "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1074916682, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1077438274, "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1078433536, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1078501524, "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1079915217, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1079329989, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1078449189, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1081171463, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1080411973, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1080932830, "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1080996782, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1078611860, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1076537334, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1080660110, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1080819130, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079178464, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1076157772, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1080086075, "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1076571955, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1080163495, "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1080219451, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1078584703, "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1080493454, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1075296522, "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1079202845, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1079926824, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1081230193, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1081105135, "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1079795613, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1079463974, "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1079444407, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1079903190, "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1078460904, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1081207600, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1081074812, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1080953162, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1081099863, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1079300110, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1081252520, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1079172191, "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1080424854, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1081114372, "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1080760606, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1075189250, "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1079570173, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1080075127, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1078595055, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1079468409, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1080145672, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1080502607, "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1080502340, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1080926573, "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1076048507, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1080816392, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1080277434, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1080714239, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1081167872, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1080154261, "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1079671943, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1080054629, "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1081251119, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1077628255, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1080366596, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1080124120, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1079025053, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1080125954, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1080867800, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1077737145, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1080574887, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1081172073, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1081179399, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1078190456, "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1080390277, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1079978829, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1080946937, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1079367285, "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1080682638, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1080971792, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1079263433, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1080410627, "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1080430542, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1080895738, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1078434029, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1073924049, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1080259017, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1080850729, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1079655605, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1080387041, "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1079343093, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1081221651, "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1076397542, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1081177873, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1079239367, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1079352529, "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1079087549, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1078482417, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1080792092, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1079632358, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1077365595, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1075872062, "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1079550292, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1080121875, "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1081105906, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1081164249, "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1081166532, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1078285680, "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1079784243, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1080046978, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1080621203, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1080622056, "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1080216947, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1076790755, "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1068192365, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1081249284, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1081247524, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1081165520, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1079436459, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1079038370, "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1070075031, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1080277163, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1081083082, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1080839624, "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1079924953, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1080398016, "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1079609998, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1080512338, "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1078518693, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1080843900, "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1080575144, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1080660969, "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1080514443, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1080363457, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1081261425, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1076752436, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1080512401, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1080456384, "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1080228703, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1080076710, "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1081258174, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1080401892, "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1081074867, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1078640549, "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1077686723, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1080320945, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079248395, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1078426961, "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1081166389, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1078686622, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1081094723, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1081230019, "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1080176930, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1079803229, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079673611, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1078233054, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1079908502, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1079527826, "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1080562605, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1081174652, "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1078929735, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1080248728, "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1079859629, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1078927303, "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1079688068, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1080394644, "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1079308365, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1079008361, "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1079848242, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1079264117, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1081162522, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1079354750, "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1081017739, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1080197625, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1081147697, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1080287449, "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1078814707, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1081075875, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1077297052, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1080050633, "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1080606523, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1079283726, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1081222491, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1080257932, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1079585134, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1080465240, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1077313155, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1078851766, "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1078960245, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1080648917, "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1078816544, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1081251736, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1080289332, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1077244681, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1080618049, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1077858275, "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1078799170, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079348470, "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1079666509, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1081082198, "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1080608335, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1080621457, "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1079921251, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1081158539, "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1080978607, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1081112679, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1080385385, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1081217328, "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1081149332, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1081122336, "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1080582549, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1079516176, "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1080969593, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1079093694, "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1078596164, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1078935452, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1079350111, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1081221007, "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1079023847, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1079608895, "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1081072525, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1078472728, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1078564434, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1081213381, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1081166471, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1079417256, "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1080364470, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1081175582, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1081163492, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1080351009, "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1081101776, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1080056639, "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1080799404, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1079636072, "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1080900001, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1079448575, "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1080587008, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1080986590, "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1080138190, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1080084354, "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1079294980, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1080094299, "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1079353703, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1079151726, "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1080483899, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1080646145, "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1079142289, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1079602727, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1080849651, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1081228727, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1080984704, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1080403374, "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1081242912, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1081026967, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1080460696, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1081259423, "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1080612143, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1080723063, "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1079248855, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1080780546, "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1079806516, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1080441261, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1077453898, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1080247674, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1078698141, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1080355089, "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1080881295, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1079811622, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1076867642, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1081094571, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1081134034, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1080584222, "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1080865938, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1079705170, "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1076780988, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1081013237, "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1080724739, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1080779670, "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1079863372, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1073819606, "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1079696768, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1079510522, "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1080144782, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1080281435, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1077139295, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1080400150, "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1081182995, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1079473261, "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1077071358, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1080213941, "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1080189615, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1078158124, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1079373779, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1081134014, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1079775161, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1079796601, "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1080678854, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1081180806, "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1079767045, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1080520578, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1080250397, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1080972653, "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1078480364, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1079044800, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1081247167, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1075756585, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1080407150, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1080959980, "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1080197041, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1081157638, "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1080207128, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1081140437, "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1079033501, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1079655535, "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1079558676, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1078165682, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1078995591, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1080759872, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1081255035, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1080580543, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1080476741, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1080757881, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079822025, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1080515140, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1079539749, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1079963816, "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1080121152, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1081172925, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1080426507, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1078715654, "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1080213044, ")", ")", "(", "speed", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1074564856, "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1075784652, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1074339727, "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1072446736, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1073117316, "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1074827114, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1073615137, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1074488023, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1074997081, "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1075981181, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1071821746, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1074062604, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1075624741, "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1071961989, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1075458517, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1074504179, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1074107911, "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1076046667, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1075752097, "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1075293420, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1075899684, "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1071340109, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1074311079, "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1074012118, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1075939713, "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1074412694, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1076098031, "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1074765307, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1074592662, "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1075989721, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1075240136, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1073854805, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1075271929, "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1071850493, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1074264448, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1075755899, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1076052999, "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1076055913, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1074411405, "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1075923567, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1074209990, "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1073654092, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1075787441, "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1073673492, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1075937607, "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1074380753, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1075322122, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1075927791, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1074921373, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1075094918, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1073526037, "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1075127073, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1074438961, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1073740026, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1075103748, "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1075814360, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1075790073, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072065907, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1076017538, "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1074054955, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1073724657, "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1075950216, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1067508717, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1074907167, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1074897845, "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1075509092, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1075303779, "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1074052097, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1071128091, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1074532259, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1074189189, "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1075079488, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1074004156, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1074555064, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1074738235, "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1075250718, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1071999352, "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1075308624, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1074382237, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1074582535, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1074929415, "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1072274534, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1073053000, "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1074402431, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072598735, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1076042670, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1075106316, "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1074038582, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1075609005, "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1073476702, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1074928255, "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1075429306, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1071812208, "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1075360454, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1075386763, "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1074288865, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1071270204, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1074250462, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1076014650, "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1073859526, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1075618480, "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1076004485, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1075941852, "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1075716374, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1075200350, "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1073151731, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1075250914, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1074408146, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1074836852, "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1075378423, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1075876521, "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1071027970, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1073906131, "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1072874417, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072402096, "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1074606227, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1074794155, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1075936655, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1072930052, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1074053293, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1075933658, "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1075536665, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1074684250, "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1075100686, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1073283678, "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1071966214, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1071262925, "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1074686702, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1074679467, "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1073596404, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1074347489, "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1076061925, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1074835630, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1075810935, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1075868839, "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1075117623, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1075707039, "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1075589507, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1073415161, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1075853919, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1073835759, "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1075119273, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1074400777, "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1075827506, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1071948635, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1076039284, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072710194, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1075919814, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1073468766, "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1075661596, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1074559135, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1074891556, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1074515109, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1074303641, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1074806355, "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1072630884, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1075630928, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1075656911, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1074349091, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1072743883, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1075918716, "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1072372267, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1074947650, "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1076083706, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1075607228, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1075796209, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1074819641, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1074143631, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1074968077, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1076038148, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1075153438, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1074637661, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1073420342, "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1072858975, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1074445206, "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1073850508, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1075849025, "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1074936933, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1074150365, "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1071732672, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1075937792, "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1075555808, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1072818910, "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1072868549, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1075524307, "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1073196992, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1072929502, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1074679623, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1075543357, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1074190000, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1072819716, "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1074814650, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1074146643, "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1072930296, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1075446987, "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1074845180, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1069825343, "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1075710251, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1074260431, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1075956902, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1075691312, "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1075936239, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1075796329, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1073519240, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1075404964, "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1076092449, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1075859352, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1075946325, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1072764778, "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1074540545, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1075899400, "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1074803351, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1075884401, "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1072167472, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1074439582, "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1073637335, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1075998056, "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1074911032, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1073829080, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072847638, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1073348815, "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1074974963, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1072709384, "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1075221343, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1075664053, "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1072749228, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1074862023, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1068599435, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1072805290, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1074190948, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1073200212, "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1074179015, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1075964268, "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1073670386, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1075965887, "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1076036879, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1074040353, "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1074743176, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1074830611, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1075333323, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1075512987, "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1075241938, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1075774876, "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1075410330, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1074772170, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1074589021, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1073982970, "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1074893764, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1075076205, "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1073735981, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1071007426, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1076100251, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1075913835, "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1075041213, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1075911407, "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1074637687, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1074017219, "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1073904118, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1075480177, "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1073809887, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1075290133, "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1075768431, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1074345535, "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1075595894, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1072870335, "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1075164666, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1074557436, "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1076092386, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1069233352, "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1075354019, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1074613452, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1075215666, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1074444548, "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1072792906, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1074887427, "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1075937795, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1075670248, "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1075877991, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1075948034, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1070822565, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1076001100, "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1074991916, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1075822566, "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1074762200, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1074792588, "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1075877032, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1075272322, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1075266811, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1073989850, "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1075036031, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1075393061, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1075533552, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1074848490, "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1073948389, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1075268736, "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1075287612, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1075343449, "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1075319724, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1075027605, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1075338819, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1075986169, "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1070534640, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1075920321, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1075489782, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1075830473, "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1072425566, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1073474782, "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1074661016, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1071129936, "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1072486558, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1071745071, "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1075854550, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1074286817, "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1074985260, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1072916178, "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1070312990, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1074930146, "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1075752561, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1075220597, "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1076038362, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1074140013, "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1075929648, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1074084218, "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1068632887, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1074952557, "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1074924535, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1075816061, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1075533253, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1075049865, "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1074408618, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1076010736, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1070977943, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1073584067, "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1075162921, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1073426199, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1075061625, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1075648128, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1067829518, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1075086774, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1076051664, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1075906204, "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1075440370, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1076092589, "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1075359550, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1075876238, "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1074809139, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1076027079, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1075319968, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1071811599, "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1072996835, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1074275729, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1076011124, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1069936549, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1070872516, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1076021869, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1075816942, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1074465290, "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1075323113, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1073832575, "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1074373897, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1075380937, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1076033946, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1075455400, "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1074574156, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1075291233, "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1075867887, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1074388050, "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1076097460, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1072117741, "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1074994148, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072766194, "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1075369156, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1074833141, "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1075877710, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1074172495, "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1076094378, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1075205762, "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1075887239, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1074961395, "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1072827122, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1074156361, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1074131757, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1074792711, "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1075370129, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1075458643, "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1073238521, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1075539632, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1074782884, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1075598078, "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1072862509, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1076099833, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1075073332, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1075800079, "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1073838484, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1074063763, "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1074883635, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1075231759, "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1075091209, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1074782889, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1075641265, ")", ")", "(", "intensity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, ")", "(", "intensityspeed", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248 ],
									"boids_data_0000000001" : [ "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, ")", "(", "maxspeed", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1080623104, ")", "(", "maxintensity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, ")", "(", "color", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1072064102, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, ")", "(", "applyrule", "(", "center", "(", "gain", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1065646817, ")", ")", "(", "avoid", "(", "gain", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, ")", "(", "thresh", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1076756480, ")", "(", "maxthresh", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", ")", "(", "align", "(", "gain", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1069547520, ")", ")", "(", "wind", "(", "gain", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1071644672, ")", "(", "speed", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3224633344, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3224633344, ")", ")", "(", "leftbarrier", "(", "gain", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, ")", "(", "position", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "repulsion", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1077149696, ")", ")", "(", "rightbarrier", "(", "gain", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, ")", "(", "position", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1084715008, ")", "(", "repulsion", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1077149696, ")", ")", "(", "topbarrier", "(", "gain", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, ")", "(", "position", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1083932672, ")", "(", "repulsion", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1077149696, ")", ")", "(", "bottombarrier", "(", "gain", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, ")", "(", "position", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "repulsion", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1083129856, ")", ")", ")", ")", "(", "(", "name", "swarm2", ")", "(", "size", 100, ")", "(", "coord", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3227940302, "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1080289597, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 3226785451, "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1078331923, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 3227838444, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1078726783, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 3227577716, "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1080089967, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 3227907444, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1080690083, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3227864234, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1076637971, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3227678708, "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1080142069, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 3227714270, "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1081257127, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 3227537404, "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1080248698, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 3227787092, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1081182243, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 3227675033, "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1081248769, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 3227133442, "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1080144098, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 3227241223, "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1081205061, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3227618187, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1076030361, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 3227480978, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1079676486, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 3227715055, "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1081082760, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 3227050513, "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1077318204, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 3227585032, "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1079525127, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 3227853396, "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1080230180, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 3227769608, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1080324246, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 3227248377, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1080060441, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 3227378344, "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1078215008, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 3227770706, "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 3225970976, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 3227220430, "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1075183802, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 3227798652, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1080731434, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3227792047, "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1077125921, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 3227814143, "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1081192228, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3227141843, "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1079111207, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3227394982, "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1080406906, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 3227301214, "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1080036090, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 3227215866, "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1081391095, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 3227118085, "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 3225828278, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 3227257589, "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1081398266, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 3227679091, "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1080584359, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 3227015864, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1080590649, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 3227869119, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1081361928, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 3227444084, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1081232093, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 3227226447, "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1079843819, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3227607116, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1078979049, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 3226863620, "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1079451595, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3227493644, "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1080104027, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3227812371, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1077796470, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 3227885082, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1079901538, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 3227587913, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1078443932, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 3227133414, "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1081088354, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 3227788331, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1079714175, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 3226840705, "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1079924771, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 3227929922, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1080133598, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 3227009361, "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1079221979, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 3227263945, "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1081045637, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3227123668, "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1081018739, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 3227056332, "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1080175117, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 3227079770, "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 3225159942, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 3227878385, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1081174768, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 3227309087, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1080815805, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 3226837029, "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1074586426, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 3227102188, "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 3224400465, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 3227937448, "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 3224700066, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3226858536, "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1080273304, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 3227618430, "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1076442675, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 3227194394, "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1078186961, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 3227741104, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1079231963, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 3227714251, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1078597843, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 3227853046, "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1080812302, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3226789521, "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1080169069, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 3227115440, "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1075952190, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 3227547306, "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1079484730, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 3227525477, "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1077988556, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 3226996806, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3222531937, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 3227312944, "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 3221729177, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 3227308819, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1079919708, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 3227917354, "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1079182271, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 3226992331, "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 3225810601, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 3227659695, "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1080339800, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 3227565533, "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1079763040, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 3227739857, "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1081330673, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 3226826219, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 3225658834, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 3226809596, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1080358608, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 3226846317, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1081238073, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 3227916534, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1075583976, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 3227682643, "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1080964535, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 3227084684, "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1080693004, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 3227881900, "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1080881234, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 3227511103, "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1079502310, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3227395216, "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1076576003, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 3227568218, "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1079202291, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 3227793695, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1079395123, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 3227205652, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1080984295, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3227833143, "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 3225538065, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 3227040459, "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1079198428, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 3227716883, "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1078666790, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 3227518718, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1081257320, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 3227557499, "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1078223454, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 3227909492, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1080617766, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 3227802886, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1081127755, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3227631838, "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 3224509263, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 3227735927, "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1080355877, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 3226857019, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3224660691, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3227806200, "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1081149227, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 3227326266, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1080052128, ")", ")", "(", "speed", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1077101213, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1074246225, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1076308362, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1077128631, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1075634908, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1076485397, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1075943501, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1076369642, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1075999237, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1073423335, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1076686711, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1076042114, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1074513807, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1076899010, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1076900978, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1077078785, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1077079465, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1076890068, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1077079151, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1076995078, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1075787286, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1076710991, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1076641791, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1074821196, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1076943900, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1074930431, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1074166009, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1077035083, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1076167842, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1076855658, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1076271092, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1075596771, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1076953331, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1076982739, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1076769711, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1076633878, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1077082812, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1075128160, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1073821963, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1073669897, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1077024644, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1077042205, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1077009359, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1075027427, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1076058427, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1073337307, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1076930058, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1076441492, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1076316806, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1074918196, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1076685227, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1076994942, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1077005926, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1076834542, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1076219961, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1076269759, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1074143691, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1075924792, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1076931754, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1076124355, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1076297903, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1077020785, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1075901324, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1077138341, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1075439863, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1076876989, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1076894107, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1075825105, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1075220854, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1077026588, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1076955168, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1076357309, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1075670639, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1075728973, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1076133094, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1076318267, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1076110585, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1076364312, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1077020213, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1076563355, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1077107645, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1074584965, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1075080329, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1077093957, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1075037210, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1075882986, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1075212512, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1075056748, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1077078100, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1076426780, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1066347255, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1076949552, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1076130939, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1075982382, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1075846622, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1074619626, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1074143064, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1070048494, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1076950895, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1076217779, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", ")", "(", "intensity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, ")", "(", "intensityspeed", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, ")", "(", "maxspeed", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1080623104, ")", "(", "maxintensity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, ")", "(", "color", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1070805811, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, ")", "(", "applyrule", "(", "center", "(", "gain", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1065646817, ")", ")", "(", "avoid", "(", "gain", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, ")", "(", "thresh", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1076756480, ")", "(", "maxthresh", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", ")", "(", "align", "(", "gain", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1069547520, ")", ")", "(", "rightbarrier", "(", "gain", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, ")", "(", "position", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1080459264, ")", "(", "repulsion", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1077805056, ")", ")", ")", ")", "(", "(", "name", "steadyswarm", ")", "(", "size", 30, ")", "(", "coord", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1081821426, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1078496374, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1081997347, "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1073756462, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1082012689, "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1078678142, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1081712649, "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1075999772, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1081976807, "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1077287553, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1082057055, "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1079552469, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1081966209, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1077992890, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1081828201, "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1078588033, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1082049759, "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1078927938, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1081804312, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1077565208, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1082080920, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1077586484, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1081901998, "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1078786864, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1081976054, "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1077745131, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1081843646, "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1077410343, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1082016214, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1076985919, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1081830065, "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1079549246, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1081940107, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1077804263, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1081699731, "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1074190852, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1081706144, "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1076910104, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1082063506, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079058811, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1081951490, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1078135887, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1082010058, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1078746980, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1081744134, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1079545219, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1081814678, "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1078886717, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1082039361, "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1079539704, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1081988633, "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1078388132, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1081921923, "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1076798375, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1081987646, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1079538576, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1081756461, "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1079270949, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1082014561, "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1078079398, ")", ")", "(", "speed", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", ")", "(", "intensity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, ")", "(", "intensityspeed", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, ")", "(", "maxspeed", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "maxintensity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, ")", "(", "color", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1070805811, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, ")", "(", "applyrule", ")", ")", ")" ],
									"boids_data_count" : [ 2 ],
									"center" : [ -168.304734, -168.939589 ],
									"fontface" : 0,
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"id" : "obj-1",
									"maxclass" : "dada.boids",
									"numinlets" : 2,
									"numoutlets" : 4,
									"out" : "nn",
									"outlettype" : [ "", "", "list", "bang" ],
									"patching_rect" : [ 13.5, 291.5, 481.0, 277.0 ],
									"showaxes" : 1,
									"showgridlabels" : 1,
									"zoom" : 60.345843
								}

							}
, 							{
								"box" : 								{
									"border" : 0,
									"filename" : "helpname.js",
									"id" : "obj-2",
									"ignoreclick" : 1,
									"jsarguments" : [ "dada.boids" ],
									"maxclass" : "jsui",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 10.0, 10.0, 231.100128, 57.567627 ]
								}

							}
 ],
						"lines" : [ 							{
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
									"source" : [ "obj-15", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-1", 0 ],
									"source" : [ "obj-17", 0 ]
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
									"source" : [ "obj-21", 0 ]
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
									"source" : [ "obj-28", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-1", 0 ],
									"source" : [ "obj-3", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-7", 0 ],
									"source" : [ "obj-32", 0 ]
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
, 							{
								"patchline" : 								{
									"destination" : [ "obj-1", 0 ],
									"source" : [ "obj-9", 0 ]
								}

							}
 ],
						"styles" : [ 							{
								"name" : "jpatcher001",
								"parentstyle" : "",
								"multi" : 0
							}
, 							{
								"name" : "preset001",
								"default" : 								{
									"accentcolor" : [ 0.5, 0.5, 0.5, 1.0 ]
								}
,
								"parentstyle" : "",
								"multi" : 0
							}
 ]
					}
,
					"patching_rect" : [ 104.0, 254.0, 56.0, 22.0 ],
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
					"varname" : "basic_tab[5]"
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
						"rect" : [ 0.0, 26.0, 976.0, 624.0 ],
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
									"id" : "obj-3",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 443.0, 71.0, 68.0, 23.0 ],
									"style" : "",
									"text" : "autozoom"
								}

							}
, 							{
								"box" : 								{
									"bubble" : 1,
									"id" : "obj-16",
									"linecount" : 2,
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 667.0, 13.567627, 113.0, 40.0 ],
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
									"patching_rect" : [ 560.0, 6.567627, 99.0, 23.0 ],
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
									"patching_rect" : [ 443.0, 6.567627, 97.0, 23.0 ],
									"style" : "",
									"text" : "domain 0 1000"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-12",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 138.5, 449.0, 94.0, 23.0 ],
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
									"patching_rect" : [ 529.0, 34.567627, 62.0, 23.0 ],
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
									"patching_rect" : [ 443.0, 34.567627, 71.0, 23.0 ],
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
									"patching_rect" : [ 404.5, 528.0, 319.0, 25.0 ],
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
									"patching_rect" : [ 373.5, 528.0, 24.0, 24.0 ],
									"style" : ""
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-5",
									"linecount" : 15,
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 424.0, 106.0, 439.0, 224.0 ],
									"style" : "",
									"text" : "Click on a boid and drag to move a flock\n\nUse spacebar to toggle play (when object has focus).\nUse Tab to autozoom\nUse Cmd+click (mac) or Ctrl+click (win) to delete elements (edges, vertices, shapes, balls).\n\nSelect items by clicking on them (use Shift to preserve selection). \nUse Cmd+A (mac) or Ctrl+A (win) to select all.\n\nUse right click contextual menu on item to mute/solo them, to make them inactive (i.e. they won't move at all) change their properties.\n\nUse right click contextual menu anywhere else to add shapes, sampling points, or to perform basic operations.",
									"textcolor" : [ 0.501961, 0.0, 0.0, 1.0 ]
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-4",
									"linecount" : 13,
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 424.0, 330.0, 430.0, 195.0 ],
									"style" : "",
									"text" : "Key-mapped tools (hold down key while them mouse is on a boid, and the pointer will changed to desired tool):\n\nS: scale swarm\nR: rotate swarm\nQ: change swarm color\n\nScroll the mouse to move the region\nCmd+Scroll (mac) or Ctrl+Scroll (win) to change zoom\nEsc to re-center\n\nCmd+Z (mac) or Ctrl+Z (win) to undo\nCmd+Shift+Z (mac) or Ctrl+Y (win) to redo",
									"textcolor" : [ 0.501961, 0.0, 0.0, 1.0 ]
								}

							}
, 							{
								"box" : 								{
									"bgimage" : "sky.jpg",
									"boids_data_0000000000" : [ "boids", "(", "rules", ")", "(", "swarms", "(", "(", "name", "swarm1", ")", "(", "size", 100, ")", "(", "coord", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1082012553, "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1079907352, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1081131245, "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1081573296, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1081501339, "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1081558792, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1080987535, "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1080673935, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1080936112, "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1081282853, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1082047687, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1081207944, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1081329571, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1081102342, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1080669085, "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1081107161, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1081988268, "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1081565757, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1081353260, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1081105538, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1081752532, "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1081206811, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1081949964, "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1079574042, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1081479049, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079730602, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1081895580, "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1080197604, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1081597910, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1081379310, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1081185618, "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1081192495, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1080835670, "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1081403902, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1081625129, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1079861734, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1081150655, "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1080801002, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1080907999, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1080844499, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1081561976, "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1080469477, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1081943184, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1080474867, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1081766315, "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1080122271, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1081364455, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1081265193, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1081362854, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1081392500, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1081681594, "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1080686956, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1081060172, "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1080049580, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1081217669, "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1079525229, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1081590435, "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1081089253, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1082066150, "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1080176665, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1081350849, "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1081147416, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1081494847, "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1080068714, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1081000227, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1080180317, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1081323872, "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1081156959, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1080728960, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079630505, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1081562808, "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1081243258, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1081350560, "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1081201980, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1081866749, "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1081452232, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1081666468, "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1080956020, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1081160448, "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1080635154, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1081978967, "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1081304572, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1080695095, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1080823431, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1081469319, "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1081602241, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1081373348, "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1080529610, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1080919024, "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1081448341, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1081394440, "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1081405580, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1081565053, "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1080682551, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1080750370, "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1080858191, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1081121901, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1080098464, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1081599645, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1081013458, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1080751892, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1081474219, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1081334163, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1080638560, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1081109144, "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1081214465, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1081570997, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1081252616, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1081350045, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1081140241, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1081315302, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1080707832, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1082015888, "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1081294174, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1081846440, "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1079783537, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1081904470, "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1081378469, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1081784472, "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1080962361, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1081605368, "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1081387608, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1081786875, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1080648507, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1081142289, "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1079457986, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1081674015, "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1081298059, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1082024000, "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1081219702, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1081117610, "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1080840649, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1081160709, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1081558073, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1081225389, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1081150297, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1081990052, "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1080557589, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1081425616, "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1080308328, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1081865488, "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1081146649, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1080701547, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1081109763, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1081479814, "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1081035472, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1081596844, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1080240678, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1081068808, "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1080195625, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1080793798, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1080856670, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1081850968, "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1079479428, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1082067945, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1081309185, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1080919621, "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1081553766, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1081345274, "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1080590155, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1081051992, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1080191343, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1081822990, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1080556196, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1082006348, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1080307726, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1081722267, "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1081265233, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1082040144, "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1080917371, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1082001599, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1080426919, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1081888733, "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1081080927, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1081419366, "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1081323340, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1081748554, "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1080314862, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1081473020, "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1081142185, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1082045693, "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1080661138, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1081604345, "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1081393439, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1081491425, "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1080555008, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1081853017, "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1079636158, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1081971069, "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1081261788, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1081893416, "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1081145664, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1081534181, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1080059120, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1081521943, "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1081325468, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1081876231, "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1081075962, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1081473556, "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1081545580, ")", ")", "(", "speed", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1074859289, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1074979209, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1074408226, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1075507081, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1075578866, "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1076026815, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1073835180, "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1075501992, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072189442, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1076022004, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1075098268, "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1075462585, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1074848198, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1074624991, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1075192662, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1075902105, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1072407710, "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1075923448, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1075745339, "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1074079396, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1075182775, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1074956539, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1076078099, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1075852941, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1075516798, "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1067908507, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1074972607, "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1076097493, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1075048899, "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1073027061, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1075706557, "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1075358360, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1073733170, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1075130498, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1074250181, "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1070902854, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1072613325, "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1075442328, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1075187086, "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1072706144, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1074636146, "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1074323399, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1075695767, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1074895975, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1075537733, "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1073877416, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1072001296, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1073283518, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1075851535, "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1075443289, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1075601742, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1075340457, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1074838497, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1073398212, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1075435610, "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1074989724, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1075685237, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1076007180, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1074905580, "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1074064070, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1074840876, "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1074846549, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1075818243, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1075511293, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1075592252, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1075745538, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1075154752, "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1075822871, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1074508070, "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1075689348, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1074176667, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1074634080, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1075552418, "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1074671364, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1073793664, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1075271807, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1074162171, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1075969840, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1075401005, "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1075349016, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1074222180, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1074111174, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1074845462, "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1075868854, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1075633384, "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1074995203, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1075926833, "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1073474577, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1071518104, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1075400938, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1073532761, "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1074296535, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1075388012, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1074314373, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1075854114, "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1075602505, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1075051262, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1074173028, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1075588309, "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1075023839, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1074955430, "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1075933604, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1076092210, "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1075716018, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1074145201, "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1075052156, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1069704598, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1075206862, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1075962563, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1074388672, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1076088121, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1074416998, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1075824679, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1076025031, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1074470813, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1074306347, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1072325124, "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1075519654, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1074341889, "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1070067518, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1074118396, "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1075242722, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1075845057, "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1075270131, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1075134529, "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1073105463, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1074831591, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1075957280, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1075261333, "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1072963803, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1074565787, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1075745887, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1075767076, "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1075383606, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1071859879, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1075866988, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1075813703, "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1075236802, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1075901625, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1076017984, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1076061460, "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1074944018, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1075590132, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1073501684, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1075039398, "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1073830234, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1075858072, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1074968721, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1072400172, "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1075869849, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1075002666, "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1075623955, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1070533394, "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1075347297, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1074103795, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1075747239, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1074898608, "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1075218994, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1075503626, "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1075182812, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1075576831, "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1075964704, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1075791701, "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1075066143, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1075548379, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1075004168, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1074497636, "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1074237063, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1076074078, "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1074027572, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1074838819, "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1073918864, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1076017249, "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1075184012, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1074745246, "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1071683140, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1073523398, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1074257124, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1074213760, "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1074154897, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1075267183, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1075397409, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1075210077, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1075057961, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1073928627, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1073907848, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1075374456, "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1074766746, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1076066533, "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1075068102, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1074003020, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1075613216, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1073438168, "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1075545992, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1073487385, "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1075249011, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1072932235, "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1075730369, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1074191547, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1072035284, ")", ")", "(", "intensity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, ")", "(", "intensityspeed", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, ")", "(", "maxspeed", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1080623104, ")", "(", "maxintensity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, ")", "(", "color", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1072064102, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, ")", "(", "applyrule", "(", "center", "(", "gain", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1065646817, ")", ")", "(", "avoid", "(", "gain", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, ")", "(", "thresh", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1076756480, ")", "(", "maxthresh", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", ")", "(", "align", "(", "gain", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1069547520, ")", ")", "(", "wind", "(", "gain", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1065646817, ")", "(", "speed", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", "(", "leftbarrier", "(", "gain", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, ")", "(", "position", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "repulsion", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1077149696, ")", ")", "(", "rightbarrier", "(", "gain", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, ")", "(", "position", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1082310656, ")", "(", "repulsion", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1077149696, ")", ")", "(", "topbarrier", "(", "gain", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, ")", "(", "position", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1081917440, ")", "(", "repulsion", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1077149696, ")", ")", "(", "bottombarrier", "(", "gain", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, ")", "(", "position", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "repulsion", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1083129856, ")", ")", ")", ")", ")" ],
									"boids_data_count" : [ 1 ],
									"center" : [ -395.092862, -292.825826 ],
									"fontface" : 0,
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"id" : "obj-1",
									"maxclass" : "dada.boids",
									"numinlets" : 2,
									"numoutlets" : 4,
									"out" : "nn",
									"outlettype" : [ "", "", "list", "bang" ],
									"patching_rect" : [ 15.5, 88.0, 377.0, 343.0 ],
									"showaxes" : 1,
									"showgridlabels" : 1,
									"zoom" : 66.789184
								}

							}
, 							{
								"box" : 								{
									"border" : 0,
									"filename" : "helpname.js",
									"id" : "obj-2",
									"ignoreclick" : 1,
									"jsarguments" : [ "dada.boids" ],
									"maxclass" : "jsui",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 10.0, 10.0, 231.100128, 57.567627 ]
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
									"source" : [ "obj-1", 3 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-1", 0 ],
									"midpoints" : [ 538.5, 73.783813, 25.0, 73.783813 ],
									"source" : [ "obj-11", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-1", 0 ],
									"midpoints" : [ 569.5, 74.783813, 25.0, 74.783813 ],
									"source" : [ "obj-14", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-1", 0 ],
									"midpoints" : [ 452.5, 74.783813, 25.0, 74.783813 ],
									"source" : [ "obj-15", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-1", 0 ],
									"source" : [ "obj-3", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-1", 0 ],
									"midpoints" : [ 452.5, 73.783813, 25.0, 73.783813 ],
									"source" : [ "obj-9", 0 ]
								}

							}
 ],
						"styles" : [ 							{
								"name" : "jpatcher001",
								"parentstyle" : "",
								"multi" : 0
							}
, 							{
								"name" : "preset001",
								"default" : 								{
									"accentcolor" : [ 0.5, 0.5, 0.5, 1.0 ]
								}
,
								"parentstyle" : "",
								"multi" : 0
							}
 ]
					}
,
					"patching_rect" : [ 87.0, 214.0, 67.0, 22.0 ],
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
					"patching_rect" : [ 299.0, 205.0, 153.0, 22.0 ],
					"saved_object_attributes" : 					{
						"filename" : "helpstarter.js",
						"parameter_enable" : 0
					}
,
					"style" : "",
					"text" : "js helpstarter.js dada.boids"
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
						"rect" : [ 100.0, 123.0, 976.0, 624.0 ],
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
									"id" : "obj-19",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 746.0, 393.0, 43.0, 23.0 ],
									"style" : "",
									"text" : "dump"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-15",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 10.0, 515.0, 68.0, 23.0 ],
									"style" : "",
									"text" : "bach.print"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-17",
									"linecount" : 2,
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 10.0, 115.0, 727.0, 36.0 ],
									"style" : "",
									"text" : "A certain number of swarms (flocks) can be defined, each containing a certain number of boids (birds). Each boid has a position and (optionally) an intensity. Each swarm undergoes a defined set of rules (see \"rule syntax\" tab).",
									"textcolor" : [ 0.501961, 0.501961, 0.501961, 1.0 ]
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-16",
									"maxclass" : "toggle",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "int" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 440.666656, 507.0, 24.0, 24.0 ],
									"style" : ""
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-11",
									"maxclass" : "newobj",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 440.666656, 542.0, 37.0, 23.0 ],
									"style" : "",
									"text" : "gate"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-7",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 481.666656, 542.0, 365.0, 21.0 ],
									"style" : "",
									"text" : "In the form: <swarm name> <boid index> <x> <y> <intensity>",
									"textcolor" : [ 0.501961, 0.501961, 0.501961, 1.0 ]
								}

							}
, 							{
								"box" : 								{
									"bubble" : 1,
									"id" : "obj-5",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 469.666656, 507.0, 275.0, 25.0 ],
									"style" : "",
									"text" : "Constantly output information on each boid"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-1",
									"linecount" : 5,
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 741.0, 292.0, 150.0, 79.0 ],
									"style" : "",
									"text" : "This is essential if you want to use dada.boids as a controller for synthesis or sampling processes",
									"textcolor" : [ 0.501961, 0.501961, 0.501961, 1.0 ]
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-14",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 440.666656, 571.0, 136.0, 23.0 ],
									"style" : "",
									"text" : "print SequencingData"
								}

							}
, 							{
								"box" : 								{
									"bubble" : 1,
									"bubbleside" : 2,
									"id" : "obj-13",
									"linecount" : 2,
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 741.0, 204.0, 153.0, 55.0 ],
									"style" : "",
									"text" : "Output boid parameters while sequencing"
								}

							}
, 							{
								"box" : 								{
									"attr" : "seq",
									"id" : "obj-12",
									"maxclass" : "attrui",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 741.0, 261.0, 150.0, 23.0 ],
									"style" : ""
								}

							}
, 							{
								"box" : 								{
									"bubble" : 1,
									"id" : "obj-10",
									"linecount" : 2,
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 465.0, 152.5, 220.0, 40.0 ],
									"style" : "",
									"text" : "Start/stop sequencing (or use spacebar when object has focus)"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-9",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 423.0, 161.0, 35.0, 23.0 ],
									"style" : "",
									"text" : "stop"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-8",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 385.0, 161.0, 34.0, 23.0 ],
									"style" : "",
									"text" : "play"
								}

							}
, 							{
								"box" : 								{
									"attr" : "showspeed",
									"id" : "obj-6",
									"maxclass" : "attrui",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 197.0, 157.0, 150.0, 23.0 ],
									"style" : ""
								}

							}
, 							{
								"box" : 								{
									"attr" : "shownames",
									"id" : "obj-3",
									"maxclass" : "attrui",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 10.0, 154.0, 150.0, 23.0 ],
									"style" : ""
								}

							}
, 							{
								"box" : 								{
									"hidden" : 1,
									"id" : "obj-34",
									"linecount" : 3,
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ -900.0, 397.0, 745.0, 52.0 ],
									"style" : "",
									"text" : "clear, addswarms ((size 100) (coord uniform 200 100 300 300) (speed uniform 0 0 10 10) (color 0.7 0 0 1) (name swarm1) (maxspeed 200) (applyrule center avoid align (wind (gain 0.01) (speed 100 100)) (leftbarrier (position 0) (repulsion 20)) (rightbarrier (position 600) (repulsion 20)) (topbarrier (position 460) (repulsion 20)) (bottombarrier (position 0) (repulsion 1000))))"
								}

							}
, 							{
								"box" : 								{
									"bgimage" : "sky.jpg",
									"boids_data_0000000000" : [ "boids", "(", "rules", ")", "(", "swarms", "(", "(", "name", "swarm1", ")", "(", "size", 100, ")", "(", "coord", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1081918180, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1080175952, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1081545874, "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1080237479, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1081782653, "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1080209734, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1081445944, "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1080944992, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1081385668, "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1080937623, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1081430037, "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1080601135, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1081889009, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1080276838, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1081973670, "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1080264891, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1081347376, "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1081002275, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1081223769, "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1080627575, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1081504454, "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1080466416, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1081307313, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1080198580, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1081836343, "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1080428296, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1081256312, "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1081030844, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1081458603, "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1080485194, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1081475854, "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1080656829, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1081516593, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1080361797, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1081531164, "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1080168586, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1081711658, "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1080067904, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1081173318, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1080665485, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1081299751, "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1080740469, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1082005613, "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1080411790, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1081460243, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1080253584, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1081219543, "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1080733225, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1081269167, "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1080543845, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1081321938, "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1080624710, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1082021373, "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1080190039, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1081484453, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1080015711, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1081849247, "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1080148465, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1081368739, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1080072908, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1081932915, "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1080359116, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1081469464, "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1080744018, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1081476974, "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1080405438, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1081235136, "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1080908068, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1081759186, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1080095687, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1081414409, "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1080180368, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1081474857, "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1080145338, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1081419409, "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1080761155, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1081628140, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1080354467, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1081656096, "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1080698548, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1081600613, "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1080691680, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1081468225, "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1080363434, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1081515209, "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1080744200, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1081786239, "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1081013694, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1081413261, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1080411223, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1081394474, "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1080499693, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1081627990, "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1080238004, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1081295969, "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1080936313, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1081598023, "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1080453348, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1081660239, "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1080084116, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1081593574, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1080930690, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1081696717, "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1080608675, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1081474292, "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1080582689, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1081776978, "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1080442185, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1081724450, "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1080274028, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1081325210, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1081095688, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1081480534, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1081003089, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1081526141, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1080323299, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1081358308, "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1080374391, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1081381689, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1080676892, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1081412397, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1080749581, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1081452700, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1080513237, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1081575719, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1080584591, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1081634380, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1080852668, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1081376058, "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1080597032, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1081426462, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1080046102, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1081477519, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1080850079, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1081840815, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1080558186, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1081260348, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1080808845, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1081314082, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1080078688, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1081394518, "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1081111696, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1081524248, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1080543191, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1081612830, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1080127942, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1081494700, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1080260589, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1081537351, "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1080954410, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1081533064, "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1080076327, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1081628426, "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1079910784, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1081403988, "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1081018382, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1081350134, "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1080738995, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1081379408, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1080829833, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1081566428, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1080786345, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1081579022, "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1080014130, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1081416064, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1080314583, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1081348652, "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1080505541, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1081334972, "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1080850262, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1081840814, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1080266151, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1081516425, "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1080852054, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1081549619, "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1080454786, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1081442717, "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1081082951, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1081588085, "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1080218745, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1081297303, "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1080445002, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1081524819, "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1080630835, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1081410098, "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1080862066, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1081188326, "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1080823865, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1081728551, "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1080451972, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1081427720, "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1080653820, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1081796236, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1080331825, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1081759582, "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1080595169, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1081679965, "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1080194336, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1081198171, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1080533534, ")", ")", "(", "speed", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 3228046376, "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 3226133893, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 3228044772, "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 3226156708, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 3228047115, "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 3226123280, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 3228035785, "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 3226279109, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 3228024609, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 3226420261, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 3228015247, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 3226499532, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 3228054115, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 3226019032, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 3228061731, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3225896958, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3228038584, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 3226241925, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 3228024036, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3226427216, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 3228037520, "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 3226256154, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3228034026, "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 3226302084, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 3228052773, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 3226039561, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 3228033339, "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 3226310963, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3228027758, "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 3226381602, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3228044600, "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 3226159145, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 3228010600, "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 3226525803, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 3228021605, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 3226456420, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 3228040256, "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 3226219319, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 3228017832, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 3226484602, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 3228025565, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 3226408613, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 3228057230, "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 3225970300, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 3228022023, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 3226451433, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 3228036813, "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 3226265546, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 3228008239, "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 3226538883, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 3228023990, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 3226427769, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 3228059325, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3225936609, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 3228031976, "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 3226328478, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 3228051299, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3226061796, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 3228038245, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 3226246465, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 3228061650, "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 3225898315, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 3228030137, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3226351834, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 3228026795, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 3226393509, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 3228020007, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 3226471857, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 3228048336, "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 3226105573, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 3228036323, "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 3226272016, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 3228023380, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 3226435146, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 3228022042, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 3226451197, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 3228040431, "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 3226216931, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 3228030428, "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 3226348148, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 3228023144, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 3226437981, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 3228019441, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 3226475190, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 3228026807, "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 3226393363, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 3228035093, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 3226288183, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3228027061, "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 3226390232, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 3228025302, "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 3226411827, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3228042170, "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 3226193073, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3228043533, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3226174129, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3228043085, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3226180379, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 3228040942, "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 3226209954, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 3228022874, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 3226441226, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3228038830, "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 3226238618, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 3228035275, "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 3226285797, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 3228048902, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3226097302, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3228053985, "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 3226021036, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 3228037555, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 3226255684, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 3228035830, "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 3226278518, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3228042358, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 3226190473, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3228032193, "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 3226325705, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 3228023786, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 3226430243, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 3228017381, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3226487225, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 3228023281, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 3226436338, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 3228021878, "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 3226453162, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 3228021089, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3226462552, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 3228013658, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 3226508595, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 3228037902, "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 3226251056, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 3228035376, "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 3226284470, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 3228046815, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3226127589, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 3228020883, "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 3226464998, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 3228037374, "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 3226258089, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3228034913, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 3226290537, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 3228007228, "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 3226544432, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 3228039290, "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 3226232414, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 3228031494, "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 3226334627, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 3228032260, "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 3226324836, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 3228016638, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3226491528, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 3228030484, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 3226347442, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3228051406, "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 3226060197, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 3228018169, "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 3226482643, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3228020437, "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 3226469322, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 3228030653, "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 3226345309, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3228029509, "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 3226359740, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 3228017166, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3226488471, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 3228018269, "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 3226482058, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3228035863, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 3226278087, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 3228047496, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 3226117770, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 3228040800, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 3226211895, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3228043236, "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 3226178275, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 3228031995, "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 3226328229, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3228044278, "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 3226163681, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3227992557, "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 3226621697, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 3228018872, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3226478530, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 3228023446, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3226434346, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 3228020141, "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 3226471068, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 3228056862, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 3225976137, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 3228035212, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 3226286619, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 3228052053, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 3226050455, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 3228042426, "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 3226189521, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3228047559, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 3226116867, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 3227995712, "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 3226605564, ")", ")", "(", "intensity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, ")", "(", "intensityspeed", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "maxspeed", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1080623104, ")", "(", "maxintensity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, ")", "(", "color", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1072064102, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, ")", "(", "applyrule", "(", "center", "(", "gain", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1065646817, ")", ")", "(", "avoid", "(", "gain", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, ")", "(", "thresh", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1076756480, ")", "(", "maxthresh", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", ")", "(", "align", "(", "gain", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1069547520, ")", ")", "(", "wind", "(", "gain", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1065646817, ")", "(", "speed", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079574528, ")", ")", "(", "leftbarrier", "(", "gain", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, ")", "(", "position", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "repulsion", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1077149696, ")", ")", "(", "rightbarrier", "(", "gain", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, ")", "(", "position", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1082310656, ")", "(", "repulsion", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1077149696, ")", ")", "(", "topbarrier", "(", "gain", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, ")", "(", "position", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1081917440, ")", "(", "repulsion", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1077149696, ")", ")", "(", "bottombarrier", "(", "gain", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, ")", "(", "position", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "repulsion", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1083129856, ")", ")", ")", ")", "(", "(", "name", "swarm2", ")", "(", "size", 25, ")", "(", "coord", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 3228183560, "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1080642777, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 3227654924, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1080255032, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 3227944871, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1080715141, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 3227104450, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1080599089, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 3226922952, "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1080075513, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 3227368304, "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1080932919, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3228222542, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1080170497, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 3227775158, "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1081035476, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 3227472493, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1080938802, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 3227237388, "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1080160747, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 3228262506, "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1080079622, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3228250820, "_x_x_x_x_bach_float64_x_x_x_x_", 1610612736, 1080429525, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 3227078437, "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1080594303, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 3227659651, "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 1080813431, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3227075672, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1080171766, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3227860750, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1080357863, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 3228244075, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1079904439, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2147483648, 3226812446, "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 1080192471, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 3228063802, "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1080871136, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 3227665011, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1080882507, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 3228119333, "_x_x_x_x_bach_float64_x_x_x_x_", 536870912, 1080590263, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 3227949904, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1080638403, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 3227936783, "_x_x_x_x_bach_float64_x_x_x_x_", 3221225472, 1080309220, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 3227699095, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1080469180, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 3758096384, 3227914709, "_x_x_x_x_bach_float64_x_x_x_x_", 2684354560, 1080563479, ")", ")", "(", "speed", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", ")", "(", "intensity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, ")", "(", "intensityspeed", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "maxspeed", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 0, ")", "(", "maxintensity", "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, ")", "(", "color", "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1067743969, "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1070889697, "_x_x_x_x_bach_float64_x_x_x_x_", 1073741824, 1067743969, "_x_x_x_x_bach_float64_x_x_x_x_", 0, 1072693248, ")", "(", "applyrule", ")", ")", ")" ],
									"boids_data_count" : [ 1 ],
									"center" : [ -311.9817, -220.464389 ],
									"fontface" : 0,
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"id" : "obj-4",
									"maxclass" : "dada.boids",
									"numinlets" : 2,
									"numoutlets" : 4,
									"out" : "nn",
									"outlettype" : [ "", "", "list", "bang" ],
									"patching_rect" : [ 10.0, 197.0, 692.0, 301.0 ],
									"showaxes" : 1,
									"showgridlabels" : 1,
									"zoom" : 51.834767
								}

							}
, 							{
								"box" : 								{
									"border" : 0,
									"filename" : "helpdetails.js",
									"id" : "obj-2",
									"ignoreclick" : 1,
									"jsarguments" : [ "dada.boids", 80 ],
									"maxclass" : "jsui",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 10.0, 10.0, 582.0, 101.0 ]
								}

							}
 ],
						"lines" : [ 							{
								"patchline" : 								{
									"destination" : [ "obj-14", 0 ],
									"source" : [ "obj-11", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-4", 0 ],
									"source" : [ "obj-12", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-11", 0 ],
									"source" : [ "obj-16", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-4", 0 ],
									"source" : [ "obj-19", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-4", 0 ],
									"source" : [ "obj-3", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-4", 0 ],
									"hidden" : 1,
									"source" : [ "obj-34", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-11", 1 ],
									"source" : [ "obj-4", 2 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-15", 0 ],
									"source" : [ "obj-4", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-4", 0 ],
									"source" : [ "obj-6", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-4", 0 ],
									"source" : [ "obj-8", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-4", 0 ],
									"source" : [ "obj-9", 0 ]
								}

							}
 ],
						"styles" : [ 							{
								"name" : "jpatcher001",
								"parentstyle" : "",
								"multi" : 0
							}
, 							{
								"name" : "preset001",
								"default" : 								{
									"accentcolor" : [ 0.5, 0.5, 0.5, 1.0 ]
								}
,
								"parentstyle" : "",
								"multi" : 0
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
					"jsarguments" : [ "dada.boids" ],
					"maxclass" : "jsui",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 10.0, 10.0, 231.100128, 57.567627 ]
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
						"rect" : [ 0.0, 26.0, 976.0, 624.0 ],
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
		"parameters" : 		{
			"obj-10::obj-64" : [ "Steer Towards Barycenter[5]", "Avoid Neighbours", 0 ],
			"obj-10::obj-19" : [ "live.gain~[1]", "live.gain~", 0 ],
			"obj-10::obj-1" : [ "Steer Towards Barycenter[2]", "Align Bird Directions", 0 ]
		}
,
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
				"name" : "helpstarter.js",
				"bootpath" : "C74:/help/resources",
				"type" : "TEXT",
				"implicit" : 1
			}
, 			{
				"name" : "dada.boids.mxo",
				"type" : "iLaX"
			}
, 			{
				"name" : "bach.print.mxo",
				"type" : "iLaX"
			}
, 			{
				"name" : "bach.post.mxo",
				"type" : "iLaX"
			}
, 			{
				"name" : "bach.keys.mxo",
				"type" : "iLaX"
			}
 ],
		"autosave" : 0
	}

}
